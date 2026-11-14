// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/task_state.hpp"

namespace robot_cleaning_manager
{
std::string_view task_state_name(TaskState state) noexcept
{
  switch (state) {
    case TaskState::idle: return "IDLE";
    case TaskState::waiting_map: return "WAITING_MAP";
    case TaskState::planning: return "PLANNING";
    case TaskState::running: return "RUNNING";
    case TaskState::paused: return "PAUSED";
    case TaskState::recovering: return "RECOVERING";
    case TaskState::stopping: return "STOPPING";
    case TaskState::canceling: return "CANCELING";
    case TaskState::succeeded: return "SUCCEEDED";
    case TaskState::failed: return "FAILED";
    case TaskState::canceled: return "CANCELED";
  }
  return "UNKNOWN";
}

bool is_terminal(TaskState state) noexcept
{
  return state == TaskState::succeeded || state == TaskState::failed ||
         state == TaskState::canceled;
}

bool TaskStateMachine::can_transition(TaskState next) const noexcept
{
  if (next == state_) {
    return state_ == TaskState::planning;
  }
  switch (state_) {
    case TaskState::idle:
      return next == TaskState::waiting_map;
    case TaskState::waiting_map:
      return next == TaskState::planning || next == TaskState::canceling ||
             next == TaskState::failed;
    case TaskState::planning:
      return next == TaskState::running || next == TaskState::canceling ||
             next == TaskState::failed;
    case TaskState::running:
      return next == TaskState::planning || next == TaskState::paused ||
             next == TaskState::recovering || next == TaskState::stopping ||
             next == TaskState::canceling || next == TaskState::succeeded ||
             next == TaskState::failed;
    case TaskState::paused:
      return next == TaskState::running || next == TaskState::stopping ||
             next == TaskState::canceling ||
             next == TaskState::failed;
    case TaskState::recovering:
      return next == TaskState::running || next == TaskState::paused ||
             next == TaskState::planning || next == TaskState::stopping ||
             next == TaskState::canceling || next == TaskState::failed;
    case TaskState::stopping:
      return next == TaskState::canceling || next == TaskState::failed;
    case TaskState::canceling:
      return next == TaskState::canceled || next == TaskState::failed;
    case TaskState::succeeded:
    case TaskState::failed:
    case TaskState::canceled:
      return next == TaskState::waiting_map;
  }
  return false;
}

bool TaskStateMachine::transition(TaskState next) noexcept
{
  if (!can_transition(next)) {
    return false;
  }
  state_ = next;
  return true;
}
}  // namespace robot_cleaning_manager
