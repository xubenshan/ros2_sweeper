// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <string_view>

namespace robot_cleaning_manager
{
enum class TaskState
{
  idle,
  waiting_map,
  planning,
  running,
  paused,
  recovering,
  stopping,
  canceling,
  succeeded,
  failed,
  canceled,
};

std::string_view task_state_name(TaskState state) noexcept;
bool is_terminal(TaskState state) noexcept;

// Owns only lifecycle policy. ROS callbacks and side effects remain in the
// manager, which must request every transition through this object.
class TaskStateMachine
{
public:
  TaskState state() const noexcept {return state_;}
  bool can_transition(TaskState next) const noexcept;
  bool transition(TaskState next) noexcept;

private:
  TaskState state_{TaskState::idle};
};
}  // namespace robot_cleaning_manager
