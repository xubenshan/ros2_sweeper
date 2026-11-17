#!/usr/bin/env python3
"""Align coverage waypoints, Nav2 plans, and Gazebo truth for offline diagnosis."""

import argparse
import csv
import json
import math
from pathlib import Path
import statistics

import matplotlib
matplotlib.use("Agg")
import matplotlib.image as mpimg
import matplotlib.pyplot as plt


FINAL_RUNS = {
    "multi_room": "final3-multi-room/multi_room/run-1",
    "islands": "final-islands/islands/run-1",
    "narrow": "final-narrow/narrow/run-1",
    "l_shape": "final-l-shape-v2/l_shape/run-1",
    "furniture": "final-furniture/furniture/run-1",
}


def read_csv(path):
    with path.open(newline="") as stream:
        return list(csv.DictReader(stream))


def write_csv(path, fieldnames, rows):
    with path.open("w", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def num(value):
    return float(value)


def stamp(row):
    return int(row["stamp_ns"])


def distance(points):
    return sum(math.hypot(x2 - x1, y2 - y1)
               for (x1, y1), (x2, y2) in zip(points, points[1:]))


def route_at(stages, timestamp):
    selected = 1
    for stage in stages:
        if stage["stamp_ns"] <= timestamp:
            selected = stage["route"]
        else:
            break
    return selected


def load_map(run_dir):
    config = {}
    for line in (run_dir / "map.yaml").read_text().splitlines():
        if ":" not in line:
            continue
        key, value = line.split(":", 1)
        config[key.strip()] = value.strip().strip("'\"")
    resolution = float(config["resolution"])
    origin = json.loads(config["origin"].replace("'", '"'))
    image = mpimg.imread(run_dir / config["image"])
    return image, resolution, origin


def plot_run(name, run_dir, output):
    waypoints = read_csv(run_dir / "waypoints.csv")
    plan_poses = read_csv(run_dir / "nav2-global-plan-poses.csv")
    truth_rows = read_csv(run_dir / "pose-comparison.csv")
    image, resolution, origin = load_map(run_dir)
    height, width = image.shape[:2]
    extent = (origin[0], origin[0] + width * resolution,
              origin[1], origin[1] + height * resolution)

    colors = {1: "#1769aa", 2: "#d95f02", 3: "#1b9e77", 4: "#7570b3",
              5: "#e7298a", 6: "#66a61e"}
    figure, axis = plt.subplots(figsize=(9, 7), dpi=150)
    axis.imshow(image, cmap="gray", origin="lower", extent=extent, alpha=0.72)

    for route in sorted({int(row["route"]) for row in waypoints}):
        points = [(num(row["x"]), num(row["y"])) for row in waypoints
                  if int(row["route"]) == route and row["type"] == "planned"]
        if len(points) > 1:
            axis.plot(*zip(*points), color=colors.get(route, "#444444"),
                      linewidth=1.4, marker="o", markersize=2.8,
                      label=f"coverage route {route}")

    plan_groups = {}
    for row in plan_poses:
        key = (int(row["goal"]), int(row["plan_for_goal"]))
        plan_groups.setdefault(key, []).append((num(row["x"]), num(row["y"])))
    for (_, plan_number), points in plan_groups.items():
        if plan_number == 1 and len(points) > 1:
            axis.plot(*zip(*points), color="#8c8c8c", linewidth=0.55,
                      alpha=0.45, zorder=2)

    truth = [(num(row["truth_x"]), num(row["truth_y"])) for row in truth_rows
             if row.get("truth_x") and row.get("truth_y")]
    if len(truth) > 1:
        axis.plot(*zip(*truth), color="#111111", linewidth=1.1,
                  alpha=0.9, label="Gazebo truth")
        axis.scatter([truth[0][0]], [truth[0][1]], color="#2ca02c", s=22,
                     label="start", zorder=5)
        axis.scatter([truth[-1][0]], [truth[-1][1]], color="#d62728", s=22,
                     label="end", zorder=5)

    axis.set_title(f"{name}: coverage waypoints, first Nav2 plans, and truth")
    axis.set_xlabel("x [m]")
    axis.set_ylabel("y [m]")
    axis.set_aspect("equal", adjustable="box")
    axis.legend(fontsize=7, loc="best", ncol=2)
    figure.tight_layout()
    figure.savefig(output / f"trajectory-{name}.png")
    plt.close(figure)


def summarize(name, run_dir):
    result = json.loads((run_dir / "result.json").read_text())
    waypoints = read_csv(run_dir / "waypoints.csv")
    plans = read_csv(run_dir / "nav2-global-plans.csv")
    poses = read_csv(run_dir / "pose-comparison.csv")

    stages = sorted(
        ({"stamp_ns": stamp(row), "route": int(row["route"])}
         for row in waypoints if row["type"] == "planned"),
        key=lambda row: row["stamp_ns"])
    goals = {}
    for row in plans:
        goals.setdefault(int(row["goal"]), []).append(row)
    first_plans = [rows[0] for rows in goals.values()]
    straight_messages = sum(row["straight"].lower() == "true" for row in plans)
    straight_first = sum(row["straight"].lower() == "true" for row in first_plans)

    stage_rows = []
    for route in sorted({int(row["route"]) for row in waypoints}):
        stage_waypoints = [row for row in waypoints if int(row["route"]) == route]
        planned = [row for row in stage_waypoints if row["type"] == "planned"]
        submitted = [row for row in stage_waypoints if row["type"] == "submitted"]
        stage_plans = [row for row in first_plans
                       if route_at(stages, stamp(row)) == route]
        stage_rows.append({
            "scene": name,
            "route": route,
            "planned_waypoints": len(planned),
            "submitted_goals": len(submitted),
            "first_nav2_plan_m": f"{sum(num(row['path_m']) for row in stage_plans):.6f}",
            "geometric_straight_first_plans": sum(
                row["straight"].lower() == "true" for row in stage_plans),
            "plan_start_ns": min((stamp(row) for row in stage_waypoints), default=""),
            "plan_end_ns": max((stamp(row) for row in stage_waypoints), default=""),
        })

    errors = [num(row["error_m"]) for row in poses if row.get("error_m")]
    truth_rows = [(num(row["truth_x"]), num(row["truth_y"])) for row in poses
                  if row.get("truth_x") and row.get("truth_y")]
    summary = {
        "scene": name,
        "truth_path_m": result.get("truth_path_m", ""),
        "path_to_90_m": result.get("path_to_90_m", ""),
        "revisit_ratio": result.get("revisit_ratio", ""),
        "task_coverage": result.get("task_coverage", ""),
        "coverage_planned_m": result.get("planned_path_m", ""),
        "coverage_planned_waypoints": result.get("planned_waypoints", ""),
        "submitted_goals": len(goals),
        "nav2_plan_messages": len(plans),
        "nav2_replans": max(0, len(plans) - len(first_plans)),
        "nav2_first_plan_m": sum(num(row["path_m"]) for row in first_plans),
        "nav2_all_plan_messages_m": sum(num(row["path_m"]) for row in plans),
        "geometric_straight_messages": straight_messages,
        "geometric_straight_first_plans": straight_first,
        "tf_truth_error_median": statistics.median(errors) if errors else "",
        "tf_truth_error_p95": (sorted(errors)[min(len(errors) - 1,
            math.ceil(0.95 * len(errors)) - 1)] if errors else ""),
        "tf_truth_error_max": max(errors) if errors else "",
        "truth_samples": len(truth_rows),
        "truth_trace_m": distance(truth_rows),
    }
    return summary, stage_rows


def plot_summary(rows, output):
    names = [row["scene"] for row in rows]
    x = list(range(len(names)))
    figure, axes = plt.subplots(1, 2, figsize=(12, 4.6), dpi=150)
    axes[0].bar([i - 0.18 for i in x], [float(row["truth_path_m"]) for row in rows],
                width=0.36, label="Gazebo truth")
    axes[0].bar([i + 0.18 for i in x], [float(row["nav2_first_plan_m"]) for row in rows],
                width=0.36, label="first Nav2 plan per goal")
    axes[0].set_ylabel("distance [m]")
    axes[0].set_title("Distance is not one common path")
    axes[0].legend(fontsize=8)
    axes[0].set_xticks(x, names, rotation=30, ha="right")

    axes[1].bar(x, [100 * float(row["revisit_ratio"]) for row in rows],
                color="#d95f02")
    axes[1].set_ylabel("revisit ratio [%]")
    axes[1].set_title("Truth revisit ratio")
    axes[1].set_xticks(x, names, rotation=30, ha="right")
    figure.tight_layout()
    figure.savefig(output / "summary-metrics.png")
    plt.close(figure)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", type=Path,
                        default=Path("results/coverage-direct-20261116"))
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    root = args.root.resolve()
    output = (args.output or root / "analysis").resolve()
    output.mkdir(parents=True, exist_ok=True)

    summaries = []
    stages = []
    for name, relative in FINAL_RUNS.items():
        run_dir = root / relative
        summary, stage_rows = summarize(name, run_dir)
        summaries.append(summary)
        stages.extend(stage_rows)
        plot_run(name, run_dir, output)
    write_csv(output / "execution-summary.csv", list(summaries[0]), summaries)
    write_csv(output / "execution-stages.csv", list(stages[0]), stages)
    plot_summary(summaries, output)
    (output / "README.md").write_text(
        "# Coverage execution analysis\n\n"
        "The CSVs align each run's coverage waypoints, first Nav2 global plan "
        "for each NavigateToPose goal, and Gazebo truth samples.\n\n"
        "`nav2_first_plan_m` sums only the first `/plan` message per goal. "
        "`nav2_all_plan_messages_m` is diagnostic only and must not be treated "
        "as traveled distance. `geometric_straight_*` detects collinear plan "
        "poses after the fact; it is not a definitive CoverageDirect hit.\n\n"
        "The trajectory PNGs show coverage waypoints by route, first Nav2 plans "
        "in gray, and the Gazebo truth trace in black.\n")
    print(output)


if __name__ == "__main__":
    main()
