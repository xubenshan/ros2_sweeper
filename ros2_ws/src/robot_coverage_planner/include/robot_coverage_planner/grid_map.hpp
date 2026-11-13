// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

namespace robot_coverage_planner
{
struct Cell
{
  int x;
  int y;
  bool operator==(Cell other) const {return x == other.x && y == other.y;}
  bool operator!=(Cell other) const {return !(*this == other);}
};

struct Region
{
  double min_x;
  double min_y;
  double max_x;
  double max_y;
};

using Mask = std::vector<std::uint8_t>;

struct GridMap
{
  int width;
  int height;
  double resolution;
  double origin_x;
  double origin_y;
  double origin_yaw;
  std::vector<std::int8_t> occupancy;

  void validate() const;
  int size() const {return width * height;}
  bool valid(Cell cell) const;
  int index(Cell cell) const {return cell.y * width + cell.x;}
  Cell cell(int index) const {return {index % width, index / width};}
  std::optional<Cell> from_world(double x, double y) const;
  std::pair<double, double> center(Cell cell) const;
  std::vector<Cell> neighbors(Cell cell) const;
  Mask drivable(double clearance) const;
  std::vector<int> manhattan_distance(const Mask & sources) const;
  bool straight(const Mask & allowed, Cell start, Cell end) const;
  double cells_for_radius(double radius) const;
  void stamp(Mask & grid, const Mask & allowed, Cell center, double radius) const;
  bool stamp_at_pose(
    Mask & grid, const Mask & allowed, double x, double y, double radius) const;
};

class Wavefront
{
public:
  Wavefront(const GridMap & grid, const Mask & allowed, Cell start);
  int cost(Cell target) const;
  std::vector<Cell> path_to(Cell target) const;
  Mask reachable() const;

private:
  const GridMap & grid_;
  std::vector<int> distance_;
  std::vector<int> parent_;
};
}  // namespace robot_coverage_planner
