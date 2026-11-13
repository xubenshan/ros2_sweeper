// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include <geometry_msgs/msg/pose_stamped.hpp>

namespace robot_cleaning_manager
{
struct Checkpoint
{
  std::string task_id;
  std::string map_id;
  std::vector<std::string> regions;
  std::vector<geometry_msgs::msg::PoseStamped> path;
  std::size_t next{0};
  std::size_t completed{0};
  std::size_t failed{0};
  std::size_t pass{0};
  std::size_t total{0};
  double distance{0.0};
  float coverage{0.0f};
  std::vector<int8_t> covered;
};

class TaskCheckpointStore
{
public:
  explicit TaskCheckpointStore(std::filesystem::path directory);
  static bool valid_id(const std::string & task_id);
  void save(const Checkpoint & checkpoint) const;
  std::optional<Checkpoint> load(const std::string & task_id) const;
  void remove(const std::string & task_id) const;

private:
  std::filesystem::path path_for(const std::string & task_id) const;
  std::filesystem::path directory_;
};
}  // namespace robot_cleaning_manager
