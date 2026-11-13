// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/checkpoint_store.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <utility>

namespace robot_cleaning_manager
{
TaskCheckpointStore::TaskCheckpointStore(std::filesystem::path directory)
: directory_(std::move(directory))
{
}

bool TaskCheckpointStore::valid_id(const std::string & task_id)
{
  return !task_id.empty() && task_id.size() <= 64 &&
    std::all_of(task_id.begin(), task_id.end(), [](unsigned char ch) {
      return std::isalnum(ch) || ch == '_' || ch == '-';
    });
}

std::filesystem::path TaskCheckpointStore::path_for(const std::string & task_id) const
{
  if (!valid_id(task_id)) {
    throw std::invalid_argument("invalid task ID");
  }
  return directory_ / (task_id + ".checkpoint");
}

void TaskCheckpointStore::save(const Checkpoint & c) const
{
  const auto target = path_for(c.task_id);
  std::filesystem::create_directories(directory_);
  auto temp = target;
  temp += ".tmp";
  {
    std::ofstream out(temp, std::ios::trunc | std::ios::binary);
    out.exceptions(std::ios::badbit | std::ios::failbit);
    out << std::setprecision(17) << "sweeper-v1 " << std::quoted(c.map_id) << ' '
        << c.next << ' ' << c.completed << ' ' << c.failed << ' ' << c.pass << ' ' << c.total
        << ' ' << c.distance << ' ' << c.coverage << '\n';
    out << c.regions.size();
    for (const auto & region : c.regions) {
      out << ' ' << std::quoted(region);
    }
    out << '\n' << c.path.size() << '\n';
    for (const auto & pose : c.path) {
      const auto & p = pose.pose.position;
      const auto & q = pose.pose.orientation;
      out << std::quoted(pose.header.frame_id) << ' ' << p.x << ' ' << p.y << ' ' << p.z
          << ' ' << q.x << ' ' << q.y << ' ' << q.z << ' ' << q.w << '\n';
    }
    out << c.covered.size() << '\n';
    out.write(reinterpret_cast<const char *>(c.covered.data()), c.covered.size());
    out.close();
  }
  std::filesystem::rename(temp, target);
}

std::optional<Checkpoint> TaskCheckpointStore::load(const std::string & task_id) const
{
  std::ifstream in(path_for(task_id), std::ios::binary);
  if (!in) {
    return std::nullopt;
  }
  Checkpoint c;
  c.task_id = task_id;
  std::string version;
  std::size_t count;
  if (!(in >> version >> std::quoted(c.map_id) >> c.next >> c.completed >> c.failed >> c.pass
      >> c.total >> c.distance >> c.coverage >> count) || version != "sweeper-v1" || count > 128 ||
    !std::isfinite(c.distance) || !std::isfinite(c.coverage))
  {
    return std::nullopt;
  }
  c.regions.resize(count);
  for (auto & region : c.regions) {
    in >> std::quoted(region);
  }
  if (!(in >> count) || count > 200000 || c.next > count) {
    return std::nullopt;
  }
  c.path.resize(count);
  for (auto & pose : c.path) {
    auto & p = pose.pose.position;
    auto & q = pose.pose.orientation;
    if (!(in >> std::quoted(pose.header.frame_id) >> p.x >> p.y >> p.z
        >> q.x >> q.y >> q.z >> q.w) || !std::isfinite(p.x) || !std::isfinite(p.y))
    {
      return std::nullopt;
    }
  }
  if (!(in >> count) || count > 10000000 || in.get() != '\n') {
    return std::nullopt;
  }
  c.covered.resize(count);
  in.read(reinterpret_cast<char *>(c.covered.data()), c.covered.size());
  return in ? std::optional<Checkpoint>(std::move(c)) : std::nullopt;
}

void TaskCheckpointStore::remove(const std::string & task_id) const
{
  std::filesystem::remove(path_for(task_id));
}
}  // namespace robot_cleaning_manager
