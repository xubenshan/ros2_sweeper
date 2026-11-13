#pragma once

namespace robot_cleaning_manager
{
constexpr bool should_retry_gap_plan_without_failure_exclusions(
  bool gap_plan, bool already_ignoring_failure_exclusions,
  bool has_failure_exclusions) noexcept
{
  return gap_plan && !already_ignoring_failure_exclusions && has_failure_exclusions;
}
}
