// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <vector>

#include <robot_cleaning_interfaces/msg/cleaning_event.hpp>

namespace robot_cleaning_manager
{
class CleaningEventLog
{
public:
  explicit CleaningEventLog(std::size_t capacity);

  robot_cleaning_interfaces::msg::CleaningEvent append(
    robot_cleaning_interfaces::msg::CleaningEvent event);

  std::vector<robot_cleaning_interfaces::msg::CleaningEvent> select(
    std::size_t limit, const std::string & task_id_filter = {},
    const std::string & code_filter = {}) const;

  std::size_t size() const noexcept {return events_.size();}
  std::size_t capacity() const noexcept {return capacity_;}

private:
  std::size_t capacity_;
  std::uint64_t next_sequence_{1};
  std::deque<robot_cleaning_interfaces::msg::CleaningEvent> events_;
};
}  // namespace robot_cleaning_manager
