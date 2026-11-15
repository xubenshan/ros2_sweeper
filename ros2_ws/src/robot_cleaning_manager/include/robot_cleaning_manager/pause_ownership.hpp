// SPDX-License-Identifier: Apache-2.0
#pragma once

namespace robot_cleaning_manager
{
enum class PauseOwner
{
  none,
  localization,
  manual,
  emergency_stop,
  cancel,
};

class PauseOwnership
{
public:
  void set(PauseOwner owner) noexcept
  {
    owner_ = owner;
    resume_pending_ = false;
  }

  void localization_recovered() noexcept
  {
    if (owner_ == PauseOwner::localization) {
      resume_pending_ = true;
    }
  }

  bool should_auto_resume(
    bool task_paused, bool localization_healthy, bool planning_in_flight,
    bool navigation_idle, bool navigation_ready, bool emergency_stop) const noexcept
  {
    return owner_ == PauseOwner::localization && resume_pending_ && task_paused &&
           localization_healthy && !planning_in_flight && navigation_idle &&
           navigation_ready && !emergency_stop;
  }

  void clear() noexcept
  {
    owner_ = PauseOwner::none;
    resume_pending_ = false;
  }

  bool localization_owned() const noexcept {return owner_ == PauseOwner::localization;}
  bool resume_pending() const noexcept {return resume_pending_;}
  PauseOwner owner() const noexcept {return owner_;}

private:
  PauseOwner owner_{PauseOwner::none};
  bool resume_pending_{false};
};
}  // namespace robot_cleaning_manager
