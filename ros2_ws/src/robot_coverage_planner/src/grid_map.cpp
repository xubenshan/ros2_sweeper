// SPDX-License-Identifier: Apache-2.0
#include "robot_coverage_planner/grid_map.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>

namespace robot_coverage_planner
{
void GridMap::validate() const
{
  if (width <= 0 || height <= 0 || static_cast<long long>(width) * height > 1000000 ||
    !std::isfinite(resolution) || resolution <= 0.0 || !std::isfinite(origin_x) ||
    !std::isfinite(origin_y) || !std::isfinite(origin_yaw) ||
    occupancy.size() != static_cast<std::size_t>(size()))
  {
    throw std::invalid_argument("invalid occupancy grid geometry");
  }
}

bool GridMap::valid(Cell cell) const
{
  return cell.x >= 0 && cell.y >= 0 && cell.x < width && cell.y < height;
}

std::optional<Cell> GridMap::from_world(double x, double y) const
{
  const double dx = x - origin_x;
  const double dy = y - origin_y;
  const double gx = (std::cos(origin_yaw) * dx + std::sin(origin_yaw) * dy) / resolution;
  const double gy = (-std::sin(origin_yaw) * dx + std::cos(origin_yaw) * dy) / resolution;
  if (!std::isfinite(gx) || !std::isfinite(gy) || gx < 0 || gy < 0 || gx >= width || gy >= height) {
    return std::nullopt;
  }
  return Cell{static_cast<int>(gx), static_cast<int>(gy)};
}

std::pair<double, double> GridMap::center(Cell cell) const
{
  const double x = (cell.x + 0.5) * resolution;
  const double y = (cell.y + 0.5) * resolution;
  return {origin_x + std::cos(origin_yaw) * x - std::sin(origin_yaw) * y,
    origin_y + std::sin(origin_yaw) * x + std::cos(origin_yaw) * y};
}

std::vector<Cell> GridMap::neighbors(Cell cell) const
{
  std::vector<Cell> result;
  for (Cell next : std::array<Cell, 4>{{
    {cell.x + 1, cell.y}, {cell.x - 1, cell.y}, {cell.x, cell.y + 1}, {cell.x, cell.y - 1}}})
  {
    if (valid(next)) {
      result.push_back(next);
    }
  }
  return result;
}

Mask GridMap::drivable(double clearance) const
{
  validate();
  if (!std::isfinite(clearance) || clearance < 0.0) {
    throw std::invalid_argument("clearance must be finite and nonnegative");
  }
  Mask result(size(), 0);
  const double cells = cells_for_radius(clearance);
  const int radius = static_cast<int>(std::min(std::ceil(cells),
      static_cast<double>(std::max(width, height))));
  const double squared = cells * cells;
  for (int i = 0; i < size(); ++i) {
    if (occupancy[i] != 0) {
      continue;
    }
    const Cell here = cell(i);
    bool free = true;
    for (int dy = -radius; dy <= radius && free; ++dy) {
      for (int dx = -radius; dx <= radius && free; ++dx) {
        if (dx * dx + dy * dy <= squared) {
          Cell point{here.x + dx, here.y + dy};
          free = valid(point) && occupancy[index(point)] == 0;
        }
      }
    }
    result[i] = free;
  }
  return result;
}

std::vector<int> GridMap::manhattan_distance(const Mask & sources) const
{
  if (sources.size() != static_cast<std::size_t>(size())) {
    throw std::invalid_argument("distance sources do not match the map");
  }
  std::vector<int> distance(size(), width + height);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const int i = index({x, y});
      if (sources[i]) {
        distance[i] = 0;
      } else {
        if (x > 0) {
          distance[i] = std::min(distance[i], distance[i - 1] + 1);
        }
        if (y > 0) {
          distance[i] = std::min(distance[i], distance[i - width] + 1);
        }
      }
    }
  }
  for (int y = height - 1; y >= 0; --y) {
    for (int x = width - 1; x >= 0; --x) {
      const int i = index({x, y});
      if (x + 1 < width) {
        distance[i] = std::min(distance[i], distance[i + 1] + 1);
      }
      if (y + 1 < height) {
        distance[i] = std::min(distance[i], distance[i + width] + 1);
      }
    }
  }
  return distance;
}

bool GridMap::straight(const Mask & allowed, Cell start, Cell end) const
{
  if (!valid(start) || !valid(end) || !allowed[index(start)] || !allowed[index(end)]) {
    return false;
  }
  const int nx = std::abs(end.x - start.x);
  const int ny = std::abs(end.y - start.y);
  const int sx = end.x > start.x ? 1 : -1;
  const int sy = end.y > start.y ? 1 : -1;
  int x = 0;
  int y = 0;
  while (x < nx || y < ny) {
    const auto a = (1 + 2LL * x) * ny;
    const auto b = (1 + 2LL * y) * nx;
    if (a == b) {
      if (!allowed[index({start.x + sx, start.y})] ||
        !allowed[index({start.x, start.y + sy})])
      {
        return false;
      }
      start.x += sx;
      start.y += sy;
      ++x;
      ++y;
    } else if (a < b) {
      start.x += sx;
      ++x;
    } else {
      start.y += sy;
      ++y;
    }
    if (!allowed[index(start)]) {
      return false;
    }
  }
  return true;
}

double GridMap::cells_for_radius(double radius) const
{
  const double cells = radius / resolution;
  const double rounded = std::round(cells);
  // ROS occupancy grid resolution is a float32. Preserve exact boundary
  // cells when a nominal integer ratio was perturbed by its serialization.
  return std::abs(cells - rounded) <= 1e-6 ? rounded : cells;
}

void GridMap::stamp(Mask & grid, const Mask & allowed, Cell center, double radius) const
{
  const double cells = cells_for_radius(radius);
  const int r = static_cast<int>(std::min(std::ceil(cells),
      static_cast<double>(std::max(width, height))));
  for (int y = std::max(0, center.y - r); y <= std::min(height - 1, center.y + r); ++y) {
    for (int x = std::max(0, center.x - r); x <= std::min(width - 1, center.x + r); ++x) {
      const int idx = index({x, y});
      const double dx = x - center.x;
      const double dy = y - center.y;
      if (allowed[idx] && dx * dx + dy * dy <= cells * cells + 1e-9) {
        grid[idx] = 1;
      }
    }
  }
}

bool GridMap::stamp_at_pose(
  Mask & grid, const Mask & allowed, double x, double y, double radius) const
{
  const auto cell = from_world(x, y);
  if (!cell) {
    return false;
  }
  const int extent = static_cast<int>(std::min(
      std::ceil(radius / resolution), static_cast<double>(std::max(width, height))));
  bool changed = false;
  for (int gy = std::max(0, cell->y - extent); gy <= std::min(height - 1, cell->y + extent); ++gy) {
    for (int gx = std::max(0, cell->x - extent); gx <= std::min(width - 1, cell->x + extent); ++gx) {
      const int i = index({gx, gy});
      const auto [cx, cy] = center({gx, gy});
      const double dx = cx - x;
      const double dy = cy - y;
      if (allowed[i] && !grid[i] && dx * dx + dy * dy <= radius * radius + 1e-9) {
        grid[i] = 1;
        changed = true;
      }
    }
  }
  return changed;
}

Wavefront::Wavefront(const GridMap & grid, const Mask & allowed, Cell start)
: grid_(grid), distance_(grid.size(), -1), parent_(grid.size(), -1)
{
  if (!grid.valid(start) || !allowed[grid.index(start)]) {
    return;
  }
  constexpr std::array<Cell, 4> offsets{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
  std::vector<int> pending{grid.index(start)};
  distance_[pending.front()] = 0;
  for (std::size_t head = 0; head < pending.size(); ++head) {
    const int ci = pending[head];
    const auto current = grid.cell(ci);
    for (const auto offset : offsets) {
      const Cell next{current.x + offset.x, current.y + offset.y};
      if (!grid.valid(next)) {
        continue;
      }
      const int ni = grid.index(next);
      if (allowed[ni] && distance_[ni] < 0) {
        distance_[ni] = distance_[ci] + 1;
        parent_[ni] = ci;
        pending.push_back(ni);
      }
    }
  }
}

int Wavefront::cost(Cell target) const
{
  return grid_.valid(target) ? distance_[grid_.index(target)] : -1;
}

std::vector<Cell> Wavefront::path_to(Cell target) const
{
  std::vector<Cell> result;
  if (cost(target) >= 0) {
    for (int i = grid_.index(target); i >= 0; i = parent_[i]) {
      result.push_back(grid_.cell(i));
    }
    std::reverse(result.begin(), result.end());
  }
  return result;
}

Mask Wavefront::reachable() const
{
  Mask result;
  result.reserve(distance_.size());
  for (int value : distance_) {
    result.push_back(value >= 0);
  }
  return result;
}
}  // namespace robot_coverage_planner
