// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/cleaning_event_log.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace robot_cleaning_manager
{
CleaningEventLog::CleaningEventLog(std::size_t capacity)
: capacity_(capacity)
{
  if (capacity_ == 0) {
    throw std::invalid_argument("event log capacity must be positive");
  }
}

robot_cleaning_interfaces::msg::CleaningEvent CleaningEventLog::append(
  robot_cleaning_interfaces::msg::CleaningEvent event)
{
  event.sequence = next_sequence_++;
  events_.push_back(event);
  while (events_.size() > capacity_) {
    events_.pop_front();
  }
  return event;
}

std::vector<robot_cleaning_interfaces::msg::CleaningEvent> CleaningEventLog::select(
  std::size_t limit, const std::string & task_id_filter, const std::string & code_filter) const
{
  limit = std::min(limit, events_.size());
  std::vector<robot_cleaning_interfaces::msg::CleaningEvent> selected;
  selected.reserve(limit);
  for (auto it = events_.rbegin(); it != events_.rend() && selected.size() < limit; ++it) {
    if (!task_id_filter.empty() && it->task_id != task_id_filter) {
      continue;
    }
    if (!code_filter.empty() && it->code != code_filter) {
      continue;
    }
    selected.push_back(*it);
  }
  return selected;
}
}  // namespace robot_cleaning_manager
