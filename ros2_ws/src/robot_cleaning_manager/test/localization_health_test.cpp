// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/localization_health.hpp"

#include <chrono>
#include <limits>

#include <gtest/gtest.h>

using namespace std::chrono_literals;
using robot_cleaning_manager::LocalizationHealthConfig;
using robot_cleaning_manager::LocalizationHealthEvaluator;
using robot_cleaning_manager::LocalizationObservation;
using robot_cleaning_manager::LocalizationState;
using robot_cleaning_manager::localization_data_fresh;
using robot_cleaning_manager::localization_recovery_evidence;
using robot_cleaning_manager::normalized_xy_covariance;

namespace
{
LocalizationObservation good(double covariance = 0.10)
{
  return LocalizationObservation{true, true, true, true, true, covariance, true};
}
}  // namespace

TEST(LocalizationHealth, WaitsForInitialData)
{
  LocalizationHealthEvaluator evaluator(LocalizationHealthConfig{});
  const auto decision = evaluator.update({}, LocalizationHealthEvaluator::TimePoint{});
  EXPECT_EQ(decision.state, LocalizationState::unknown);
  EXPECT_FALSE(decision.operational);
}

TEST(LocalizationHealth, InitialDegradationIsNotOperational)
{
  LocalizationHealthEvaluator evaluator(LocalizationHealthConfig{});
  const auto decision = evaluator.update(good(0.60), LocalizationHealthEvaluator::TimePoint{});
  EXPECT_EQ(decision.state, LocalizationState::degraded);
  EXPECT_EQ(
    evaluator.update(good(0.60), LocalizationHealthEvaluator::TimePoint{} + 30s).state,
    LocalizationState::degraded);
  EXPECT_EQ(
    evaluator.update(good(0.10), LocalizationHealthEvaluator::TimePoint{} + 31s).state,
    LocalizationState::healthy);
  EXPECT_FALSE(decision.operational);
}

TEST(LocalizationHealth, StaleDataOnlyFailsWhileMoving)
{
  EXPECT_TRUE(localization_data_fresh(false, 30.0, 2.0));
  EXPECT_FALSE(localization_data_fresh(true, 2.01, 2.0));
  EXPECT_TRUE(localization_data_fresh(true, 2.0, 2.0));
}
TEST(LocalizationHealth, CovarianceNormalizationAllowsOnlyNumericalRoundoff)
{
  ASSERT_TRUE(normalized_xy_covariance(-2.7e-13, 4.0e-13));
  EXPECT_DOUBLE_EQ(*normalized_xy_covariance(-2.7e-13, 4.0e-13), 4.0e-13);
  EXPECT_FALSE(normalized_xy_covariance(-1.0e-5, 0.1));
  EXPECT_FALSE(normalized_xy_covariance(
    std::numeric_limits<double>::quiet_NaN(), 0.1));
}

TEST(LocalizationHealth, RecoveryEvidenceMustBeNewAndCurrentlyFresh)
{
  EXPECT_FALSE(localization_recovery_evidence(false, 0.1, 2.0));
  EXPECT_TRUE(localization_recovery_evidence(true, 2.0, 2.0));
  EXPECT_FALSE(localization_recovery_evidence(true, 2.01, 2.0));
  EXPECT_FALSE(localization_recovery_evidence(
    true, std::numeric_limits<double>::quiet_NaN(), 2.0));
}



TEST(LocalizationHealth, AppliesLossAndRecoveryHysteresis)
{
  LocalizationHealthEvaluator evaluator(LocalizationHealthConfig{});
  const auto start = LocalizationHealthEvaluator::TimePoint{};
  EXPECT_EQ(evaluator.update(good(), start).state, LocalizationState::healthy);

  auto high = good(0.60);
  auto decision = evaluator.update(high, start + 100ms);
  EXPECT_EQ(decision.state, LocalizationState::degraded);
  EXPECT_TRUE(decision.operational);
  EXPECT_EQ(evaluator.update(high, start + 1099ms).state, LocalizationState::degraded);
  decision = evaluator.update(high, start + 1100ms);
  EXPECT_EQ(decision.state, LocalizationState::lost);
  EXPECT_FALSE(decision.operational);

  EXPECT_EQ(evaluator.update(good(0.20), start + 1200ms).state, LocalizationState::lost);
  EXPECT_EQ(evaluator.update(good(0.20), start + 3199ms).state, LocalizationState::lost);
  decision = evaluator.update(good(0.20), start + 3200ms);
  EXPECT_EQ(decision.state, LocalizationState::healthy);
  EXPECT_TRUE(decision.operational);
}

TEST(LocalizationHealth, TransientDegradationDoesNotPause)
{
  LocalizationHealthEvaluator evaluator(LocalizationHealthConfig{});
  const auto start = LocalizationHealthEvaluator::TimePoint{};
  evaluator.update(good(), start);
  auto stale = good();
  stale.pose_fresh = false;
  EXPECT_EQ(evaluator.update(stale, start + 10ms).state, LocalizationState::degraded);
  const auto cleared = evaluator.update(good(), start + 500ms);
  EXPECT_EQ(cleared.state, LocalizationState::healthy);
  EXPECT_TRUE(cleared.operational);
}

TEST(LocalizationHealth, RejectsInvalidCovarianceAndMissingTransform)
{
  LocalizationHealthConfig config;
  config.lost_hold = 0ms;
  LocalizationHealthEvaluator evaluator(config);
  const auto start = LocalizationHealthEvaluator::TimePoint{};
  evaluator.update(good(), start);
  auto invalid = good();
  invalid.covariance_valid = false;
  evaluator.update(invalid, start + 1ms);
  EXPECT_EQ(evaluator.update(invalid, start + 1ms).state, LocalizationState::lost);

  LocalizationHealthEvaluator missing_tf(config);
  missing_tf.update(good(), start);
  auto observation = good();
  observation.transform_available = false;
  missing_tf.update(observation, start + 1ms);
  EXPECT_EQ(missing_tf.update(observation, start + 1ms).state, LocalizationState::lost);
}

TEST(LocalizationHealth, LostStateRequiresNewEvidenceBeforeRecovery)
{
  LocalizationHealthConfig config;
  config.lost_hold = 0ms;
  LocalizationHealthEvaluator evaluator(config);
  const auto start = LocalizationHealthEvaluator::TimePoint{};
  evaluator.update(good(), start);
  auto bad = good(0.60);
  evaluator.update(bad, start + 1ms);
  EXPECT_EQ(evaluator.update(bad, start + 1ms).state, LocalizationState::lost);

  auto stale_but_low_covariance = good(0.20);
  stale_but_low_covariance.recovery_evidence = false;
  EXPECT_EQ(
    evaluator.update(stale_but_low_covariance, start + 5s).state,
    LocalizationState::lost);
  EXPECT_EQ(evaluator.update(good(0.20), start + 5100ms).state, LocalizationState::lost);
  EXPECT_EQ(evaluator.update(good(0.20), start + 7100ms).state, LocalizationState::healthy);
}

TEST(LocalizationHealth, SlamModeDoesNotRequireCovariance)
{
  LocalizationHealthEvaluator evaluator(LocalizationHealthConfig{});
  LocalizationObservation observation;
  observation.covariance_required = false;
  observation.pose_fresh = true;
  observation.transform_available = true;
  const auto decision = evaluator.update(observation, LocalizationHealthEvaluator::TimePoint{});
  EXPECT_EQ(decision.state, LocalizationState::healthy);
  EXPECT_TRUE(decision.operational);
}
