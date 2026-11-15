// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/localization_health.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace robot_cleaning_manager
{
LocalizationHealthEvaluator::LocalizationHealthEvaluator(LocalizationHealthConfig config)
: config_(config)
{
  if (!std::isfinite(config_.lost_covariance_threshold) ||
    !std::isfinite(config_.recovered_covariance_threshold) ||
    config_.recovered_covariance_threshold < 0.0 ||
    config_.lost_covariance_threshold <= config_.recovered_covariance_threshold ||
    config_.lost_hold.count() < 0 || config_.recovered_hold.count() < 0)
  {
    throw std::invalid_argument("invalid localization health thresholds");
  }
}

bool localization_data_fresh(bool moving, double age_s, double timeout_s) noexcept
{
  return !moving ||
         (std::isfinite(age_s) && age_s >= 0.0 && std::isfinite(timeout_s) && age_s <= timeout_s);
}

std::optional<double> normalized_xy_covariance(double xx, double yy) noexcept
{
  constexpr double kRoundoffTolerance = 1e-9;
  if (!std::isfinite(xx) || !std::isfinite(yy) ||
    xx < -kRoundoffTolerance || yy < -kRoundoffTolerance)
  {
    return std::nullopt;
  }
  return std::max(0.0, xx) + std::max(0.0, yy);
}

bool localization_recovery_evidence(bool new_sample, double age_s, double timeout_s) noexcept
{
  return new_sample && std::isfinite(age_s) && age_s >= 0.0 &&
         std::isfinite(timeout_s) && age_s <= timeout_s;
}

const char * localization_state_name(LocalizationState state) noexcept
{
  switch (state) {
    case LocalizationState::unknown: return "UNKNOWN";
    case LocalizationState::healthy: return "HEALTHY";
    case LocalizationState::degraded: return "DEGRADED";
    case LocalizationState::lost: return "LOST";
  }
  return "UNKNOWN";
}

std::string LocalizationHealthEvaluator::failure_reason(
  const LocalizationObservation & observation, double threshold)
{
  if (!observation.transform_available) {
    return "map-to-base transform unavailable";
  }
  if (!observation.pose_fresh) {
    return "localization pose stale while robot is moving";
  }
  if (observation.covariance_required && !observation.pose_received) {
    return "waiting for localization pose";
  }
  if (observation.covariance_required && !observation.covariance_valid) {
    return "localization covariance is invalid";
  }
  if (observation.covariance_required && observation.covariance_xy > threshold) {
    return "localization covariance exceeds loss threshold";
  }
  return "localization healthy";
}

LocalizationDecision LocalizationHealthEvaluator::result(bool changed, std::string reason) const
{
  return LocalizationDecision{
    state_, operational_,
    changed, std::move(reason)};
}

LocalizationDecision LocalizationHealthEvaluator::update(
  const LocalizationObservation & observation, TimePoint now)
{
  const bool covariance_bad = observation.covariance_required &&
    (!observation.pose_received || !observation.covariance_valid ||
    observation.covariance_xy > config_.lost_covariance_threshold);
  const bool bad = !observation.transform_available || !observation.pose_fresh || covariance_bad;
  const bool recovered = observation.transform_available && observation.pose_fresh &&
    (!observation.covariance_required ||
    (observation.pose_received && observation.covariance_valid &&
    observation.covariance_xy <= config_.recovered_covariance_threshold));

  if (state_ == LocalizationState::unknown) {
    if (recovered || (!bad && observation.pose_received)) {
      state_ = LocalizationState::healthy;
      operational_ = true;
      candidate_since_.reset();
      return result(true, "localization data available");
    }
    if (observation.pose_received || observation.transform_available) {
      state_ = LocalizationState::degraded;
      candidate_since_ = now;
      return result(true, failure_reason(observation, config_.lost_covariance_threshold));
    }
    return result(false, "waiting for localization data");
  }

  if (state_ == LocalizationState::healthy) {
    if (!bad) {
      return result(false, "localization healthy");
    }
    state_ = LocalizationState::degraded;
    candidate_since_ = now;
    return result(true, failure_reason(observation, config_.lost_covariance_threshold));
  }

  if (state_ == LocalizationState::degraded) {
    if (!bad) {
      state_ = LocalizationState::healthy;
      operational_ = true;
      candidate_since_.reset();
      return result(true, "transient localization degradation cleared");
    }
    if (!operational_) {
      return result(false, failure_reason(observation, config_.lost_covariance_threshold));
    }

    if (candidate_since_ && now - *candidate_since_ >= config_.lost_hold) {
      state_ = LocalizationState::lost;
      operational_ = false;
      candidate_since_.reset();
      return result(true, failure_reason(observation, config_.lost_covariance_threshold));
    }
    return result(false, failure_reason(observation, config_.lost_covariance_threshold));
  }

  if (!recovered || !observation.recovery_evidence) {
    candidate_since_.reset();
    return result(
      false, recovered ? "waiting for new localization evidence" :
      failure_reason(observation, config_.recovered_covariance_threshold));
  }
  if (!candidate_since_) {
    candidate_since_ = now;
    return result(false, "localization recovery candidate");
  }
  if (now - *candidate_since_ >= config_.recovered_hold) {
    state_ = LocalizationState::healthy;
    operational_ = true;
    candidate_since_.reset();
    return result(true, "localization recovered and stable");
  }
  return result(false, "localization recovery candidate");
}
}  // namespace robot_cleaning_manager
