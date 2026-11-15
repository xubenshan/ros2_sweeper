// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/task_state.hpp"

#include <initializer_list>

#include <gtest/gtest.h>

using robot_cleaning_manager::TaskState;
using robot_cleaning_manager::TaskStateMachine;
using robot_cleaning_manager::is_terminal;
using robot_cleaning_manager::task_state_name;

TEST(TaskState, PreservesPublicStateNames)
{
  EXPECT_EQ(task_state_name(TaskState::waiting_map), "WAITING_MAP");
  EXPECT_EQ(task_state_name(TaskState::canceling), "CANCELING");
  EXPECT_EQ(task_state_name(TaskState::succeeded), "SUCCEEDED");
  EXPECT_TRUE(is_terminal(TaskState::failed));
  EXPECT_FALSE(is_terminal(TaskState::paused));
}

TEST(TaskState, NormalPlanningAndCompletion)
{
  TaskStateMachine machine;
  EXPECT_TRUE(machine.transition(TaskState::waiting_map));
  EXPECT_TRUE(machine.transition(TaskState::planning));
  EXPECT_TRUE(machine.transition(TaskState::running));
  EXPECT_TRUE(machine.transition(TaskState::planning));  // gap-fill request
  EXPECT_TRUE(machine.transition(TaskState::running));
  EXPECT_TRUE(machine.transition(TaskState::succeeded));
  EXPECT_EQ(machine.state(), TaskState::succeeded);
}

TEST(TaskState, PauseResumeAndCancel)
{
  TaskStateMachine machine;
  ASSERT_TRUE(machine.transition(TaskState::waiting_map));
  ASSERT_TRUE(machine.transition(TaskState::planning));
  ASSERT_TRUE(machine.transition(TaskState::running));
  EXPECT_TRUE(machine.transition(TaskState::paused));
  EXPECT_TRUE(machine.transition(TaskState::running));
  EXPECT_TRUE(machine.transition(TaskState::canceling));
  EXPECT_TRUE(machine.transition(TaskState::canceled));
}

TEST(TaskState, NavigationFailureRecoveryAndStop)
{
  TaskStateMachine machine;
  ASSERT_TRUE(machine.transition(TaskState::waiting_map));
  ASSERT_TRUE(machine.transition(TaskState::planning));
  ASSERT_TRUE(machine.transition(TaskState::running));
  EXPECT_TRUE(machine.transition(TaskState::recovering));
  EXPECT_TRUE(machine.transition(TaskState::running));
  EXPECT_TRUE(machine.transition(TaskState::stopping));
  EXPECT_TRUE(machine.transition(TaskState::failed));
}

TEST(TaskState, UnconfirmedPauseCancelRevokesMotionAuthority)
{
  TaskStateMachine machine;
  ASSERT_TRUE(machine.transition(TaskState::waiting_map));
  ASSERT_TRUE(machine.transition(TaskState::planning));
  ASSERT_TRUE(machine.transition(TaskState::running));
  ASSERT_TRUE(machine.transition(TaskState::paused));
  EXPECT_TRUE(machine.transition(TaskState::stopping));
  EXPECT_TRUE(machine.transition(TaskState::failed));
}

TEST(TaskState, PlanningFailureAndNextTask)
{
  TaskStateMachine machine;
  ASSERT_TRUE(machine.transition(TaskState::waiting_map));
  ASSERT_TRUE(machine.transition(TaskState::planning));
  EXPECT_TRUE(machine.transition(TaskState::failed));
  EXPECT_TRUE(machine.transition(TaskState::waiting_map));
}

TEST(TaskState, RejectsIllegalTransitions)
{
  TaskStateMachine machine;
  EXPECT_FALSE(machine.transition(TaskState::running));
  EXPECT_EQ(machine.state(), TaskState::idle);
  ASSERT_TRUE(machine.transition(TaskState::waiting_map));
  EXPECT_FALSE(machine.transition(TaskState::recovering));
  EXPECT_EQ(machine.state(), TaskState::waiting_map);
}

TEST(TaskState, CancelIsLegalFromEveryAsynchronousActivePhase)
{
  const auto expect_cancel = [](std::initializer_list<TaskState> prefix) {
      TaskStateMachine machine;
      for (const auto state : prefix) {
        EXPECT_TRUE(machine.transition(state));
      }
      EXPECT_TRUE(machine.transition(TaskState::canceling));
      EXPECT_TRUE(machine.transition(TaskState::canceled));
    };
  expect_cancel({TaskState::waiting_map});
  expect_cancel({TaskState::waiting_map, TaskState::planning});
  expect_cancel({TaskState::waiting_map, TaskState::planning, TaskState::running,
    TaskState::paused});
  expect_cancel({TaskState::waiting_map, TaskState::planning, TaskState::running,
    TaskState::recovering});
}

TEST(TaskState, RouteReadyWhileLocalizationLostMayPauseFromPlanning)
{
  TaskStateMachine machine;
  ASSERT_TRUE(machine.transition(TaskState::waiting_map));
  ASSERT_TRUE(machine.transition(TaskState::planning));
  EXPECT_TRUE(machine.transition(TaskState::paused));
  EXPECT_TRUE(machine.transition(TaskState::running));
}
