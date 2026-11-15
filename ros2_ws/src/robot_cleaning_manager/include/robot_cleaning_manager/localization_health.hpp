// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace robot_cleaning_manager
{
enum class LocalizationState : std::uint8_t
{
  unknown,
  healthy,
  degraded,
  lost,
};

struct LocalizationHealthConfig
{
  double lost_covariance_threshold{0.50};
  double recovered_covariance_threshold{0.25};
  std::chrono::milliseconds lost_hold{1000};
  std::chrono::milliseconds recovered_hold{2000};
};

struct LocalizationObservation
{
  bool covariance_required{true};
  bool pose_received{false};
  bool pose_fresh{false};
  bool transform_available{false};
  bool covariance_valid{false};
  double covariance_xy{0.0};
  bool recovery_evidence{false};
};

struct LocalizationDecision
{
  LocalizationState state{LocalizationState::unknown};
  bool operational{false};
  bool changed{false};
  std::string reason;
};

class LocalizationHealthEvaluator
{
public:
  using TimePoint = std::chrono::steady_clock::time_point;

  explicit LocalizationHealthEvaluator(LocalizationHealthConfig config);
  LocalizationDecision update(const LocalizationObservation & observation, TimePoint now);
  LocalizationState state() const noexcept {return state_;}

private:
  static std::string failure_reason(const LocalizationObservation & observation, double threshold);
  LocalizationDecision result(bool changed, std::string reason) const;

  LocalizationHealthConfig config_;
  LocalizationState state_{LocalizationState::unknown};
  bool operational_{false};
  std::optional<TimePoint> candidate_since_;
};

bool localization_data_fresh(bool moving, double age_s, double timeout_s) noexcept;
std::optional<double> normalized_xy_covariance(double xx, double yy) noexcept;

bool localization_recovery_evidence(bool new_sample, double age_s, double timeout_s) noexcept;


const char * localization_state_name(LocalizationState state) noexcept;
}  // namespace robot_cleaning_manager
