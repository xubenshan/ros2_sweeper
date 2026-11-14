// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "robot_coverage_planner/coverage_plan.hpp"

namespace robot_coverage_planner
{
// Deliberately simple comparison planner: fixed-orientation boustrophedon
// lanes plus nearest-missing-floor gap repair. It shares geometry and business
// inputs with CoveragePlan but none of its route ranking/refinement logic.
class BaselineCoveragePlan
{
public:
  BaselineCoveragePlan(const GridMap & grid, PlanOptions options, Cell start,
    const Mask & blocked_centers = {});

  const Mask & reachable() const {return geometry_.reachable();}
  Mask target_floor(const std::vector<Region> & regions) const;
  std::vector<Cell> sweep(
    Cell start, const std::vector<Region> & regions, double target_coverage = 0.90,
    const Mask & task_floor = {}) const;
  std::vector<Cell> gaps(
    Cell start, const std::vector<Region> & regions, const Mask & covered,
    const std::vector<Cell> & excluded, const Mask & priority = {},
    const Mask & task_floor = {}, double target_coverage = 0.0,
    double distance_budget = 0.0) const;

private:
  Mask center_mask(const std::vector<Region> & regions) const;
  void append_connector(std::vector<Cell> & path, Cell & from, Cell to) const;
  double trace(Cell start, const std::vector<Cell> & path, const Mask & target, Mask & swept) const;
  std::vector<Cell> gap_route(
    Cell start, Mask missing, const std::vector<Cell> & excluded,
    int desired, double distance_budget, int & deficit) const;

  const GridMap & grid_;
  PlanOptions options_;
  CoveragePlan geometry_;
};
}  // namespace robot_coverage_planner
