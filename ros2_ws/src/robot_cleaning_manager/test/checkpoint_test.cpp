// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/checkpoint_store.hpp"
#include "robot_cleaning_manager/recovery_executor.hpp"


#include <gtest/gtest.h>
#include <cstdlib>

using robot_cleaning_manager::Checkpoint;
using robot_cleaning_manager::TaskCheckpointStore;

TEST(CheckpointStore, RoundTripAndAtomicReplacement)
{
  char directory[] = "/tmp/sweeper-checkpoint-XXXXXX";
  ASSERT_NE(mkdtemp(directory), nullptr);
  const TaskCheckpointStore store(directory);
  Checkpoint checkpoint;
  checkpoint.task_id = "task-1";
  checkpoint.map_id = "living-room";
  checkpoint.regions = {"north_west", "north_east"};
  checkpoint.path.resize(2);
  checkpoint.path.back().header.frame_id = "map";
  checkpoint.path.back().pose.position.x = 1.25;
  checkpoint.next = 1;
  checkpoint.covered = {0, -1, 100, 0};
  store.save(checkpoint);
  auto loaded = store.load(checkpoint.task_id);
  ASSERT_TRUE(loaded);
  EXPECT_EQ(loaded->next, 1u);
  EXPECT_EQ(loaded->regions, checkpoint.regions);
  EXPECT_EQ(loaded->covered, checkpoint.covered);
  EXPECT_DOUBLE_EQ(loaded->path.back().pose.position.x, 1.25);
  checkpoint.next = 2;
  store.save(checkpoint);
  EXPECT_EQ(store.load(checkpoint.task_id)->next, 2u);
  EXPECT_FALSE(TaskCheckpointStore::valid_id("../outside"));
  store.remove(checkpoint.task_id);
  EXPECT_FALSE(store.load(checkpoint.task_id));
  std::filesystem::remove_all(directory);
}

TEST(CheckpointStore, RejectsTruncatedData)
{
  char directory[] = "/tmp/sweeper-truncated-XXXXXX";
  ASSERT_NE(mkdtemp(directory), nullptr);
  const TaskCheckpointStore store(directory);
  Checkpoint checkpoint;
  checkpoint.task_id = "interrupted";
  checkpoint.map_id = "map";
  checkpoint.covered = {100, 0, 100, -1};
  store.save(checkpoint);
  const auto file = std::filesystem::path(directory) / "interrupted.checkpoint";
  std::filesystem::resize_file(file, std::filesystem::file_size(file) - 1);
  EXPECT_FALSE(store.load(checkpoint.task_id));
  std::filesystem::remove_all(directory);
}

TEST(RecoveryExecutor, ReverseThenTurnAwayFromContact)
{
  using namespace std::chrono_literals;
  const robot_cleaning_manager::RecoveryExecutor left("left");
  const robot_cleaning_manager::RecoveryExecutor right("right");
  EXPECT_LT(left.command(300ms).linear.x, 0.0);
  EXPECT_DOUBLE_EQ(left.command(300ms).angular.z, 0.0);
  EXPECT_DOUBLE_EQ(left.command(1700ms).linear.x, 0.0);
  EXPECT_LT(left.command(1700ms).angular.z, 0.0);
  EXPECT_GT(right.command(1700ms).angular.z, 0.0);
  EXPECT_FALSE(left.done(1700ms));
  EXPECT_TRUE(left.done(2500ms));
}
