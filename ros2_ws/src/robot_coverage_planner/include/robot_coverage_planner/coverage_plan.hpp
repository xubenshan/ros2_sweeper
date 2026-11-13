// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "robot_coverage_planner/grid_map.hpp"

namespace robot_coverage_planner
{
struct Span
{
  int y;
  int first;
  int last;
};

using SweepCell = std::vector<Span>;

struct PlanOptions
{
  double robot_radius{0.175};
  double safety_margin{0.005};
  double cleaning_radius{0.20};
  double row_overlap{0.10};
  double waypoint_spacing{0.40};
  double turn_cost{0.20};
  double edge_margin{0.0};
  bool refine_sweep{false};
};

std::vector<SweepCell> decompose(const GridMap & grid, const Mask & reachable);

class CoveragePlan
{
public:
  CoveragePlan(const GridMap & grid, PlanOptions options, Cell start,
    const Mask & blocked_centers = {});

  const Mask & reachable() const {return reachable_;}
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
  Mask within(const std::vector<Region> & regions) const;
  void append(
    std::vector<Cell> & path, Cell & from, Cell to, const Wavefront * distances = nullptr) const;
  std::vector<std::vector<Cell>> lanes(
    const Mask & allowed, bool vertical, int phase, int spacing, double slope = 0.0) const;
  std::vector<Cell> order_lanes(
    Cell start, double heading, std::vector<std::vector<Cell>> lanes) const;
  std::vector<Cell> open_floor_route(
    Cell start, const Mask & allowed, const Mask & target, double target_coverage) const;
  std::vector<Cell> connect_strips(
    Cell start, const std::vector<std::vector<Cell>> & strips, const Mask & target,
    int desired, double & best_score) const;
  double score_open_floor_route(
    Cell start, const Mask & target, int desired, std::vector<Cell> & route) const;
  std::vector<Cell> refine_sweep(
    Cell start, const Mask & target, int desired, std::vector<Cell> route) const;
  double trace(Cell start, const std::vector<Cell> & path, const Mask & target, Mask & swept) const;
  double route_cost(Cell start, const std::vector<Cell> & path, const Mask & target) const;
  std::vector<Cell> gap_route(
    Cell start, Mask missing, const std::vector<Cell> & excluded, const Mask & priority,
    int desired, double distance_budget, double distance_weight, int seed,
    int & coverage_deficit, double & distance) const;
  const GridMap & grid_;
  PlanOptions options_;
  Mask reachable_;
};
}  // namespace robot_coverage_planner
