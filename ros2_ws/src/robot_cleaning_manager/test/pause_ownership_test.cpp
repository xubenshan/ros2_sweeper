// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/pause_ownership.hpp"

#include <gtest/gtest.h>

using robot_cleaning_manager::PauseOwner;
using robot_cleaning_manager::PauseOwnership;

TEST(PauseOwnership, LocalizationPauseMayAutoResumeAfterAllGuardsClear)
{
  PauseOwnership ownership;
  ownership.set(PauseOwner::localization);
  ownership.localization_recovered();
  EXPECT_TRUE(ownership.should_auto_resume(true, true, false, true, true, false));
  EXPECT_FALSE(ownership.should_auto_resume(true, true, true, true, true, false));
  EXPECT_FALSE(ownership.should_auto_resume(true, true, false, false, true, false));
}

TEST(PauseOwnership, ManualPauseNeverAutoResumesAfterLocalizationRecovery)
{
  PauseOwnership ownership;
  ownership.set(PauseOwner::manual);
  ownership.localization_recovered();
  EXPECT_FALSE(ownership.resume_pending());
  EXPECT_FALSE(ownership.should_auto_resume(true, true, false, true, true, false));
}

TEST(PauseOwnership, EmergencyStopRevokesLocalizationResume)
{
  PauseOwnership ownership;
  ownership.set(PauseOwner::localization);
  ownership.localization_recovered();
  ownership.set(PauseOwner::emergency_stop);
  EXPECT_EQ(ownership.owner(), PauseOwner::emergency_stop);
  EXPECT_FALSE(ownership.resume_pending());
}

TEST(PauseOwnership, CancelWinsRecoveryRace)
{
  PauseOwnership ownership;
  ownership.set(PauseOwner::localization);
  ownership.set(PauseOwner::cancel);
  ownership.localization_recovered();
  EXPECT_EQ(ownership.owner(), PauseOwner::cancel);
  EXPECT_FALSE(ownership.should_auto_resume(true, true, false, true, true, false));
}
