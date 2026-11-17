#!/usr/bin/env python3
"""Verify benchmark coordinate and timestamp alignment."""

import argparse
import csv
import math
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.image as mpimg
import matplotlib.pyplot as plt


RUNS = {
    "multi_room": "final3-multi-room/multi_room/run-1",
    "islands": "final-islands/islands/run-1",
    "narrow": "final-narrow/narrow/run-1",
    "l_shape": "final-l-shape-v2/l_shape/run-1",
    "furniture": "final-furniture/furniture/run-1",
}


def read_csv(path):
    with path.open(newline="") as stream:
        return list(csv.DictReader(stream))


def median(values):
    ordered = sorted(values)
    if not ordered:
        return float("nan")
    middle = len(ordered) // 2
    if len(ordered) % 2:
        return ordered[middle]
    return 0.5 * (ordered[middle - 1] + ordered[middle])


def percentile(values, fraction):
    ordered = sorted(values)
    if not ordered:
        return float("nan")
    index = min(len(ordered) - 1, max(0, math.ceil(fraction * len(ordered)) - 1))
    return ordered[index]


def fit_se2(rows):
    """Return (dx, dy, yaw) for truth ~= R(tf) + t."""
    tf = [(float(row["tf_x"]), float(row["tf_y"])) for row in rows]
    truth = [(float(row["truth_x"]), float(row["truth_y"])) for row in rows]
    tf_mean = tuple(sum(point[i] for point in tf) / len(tf) for i in (0, 1))
    truth_mean = tuple(sum(point[i] for point in truth) / len(truth) for i in (0, 1))
    cross = 0.0
    dot = 0.0
    for (px, py), (qx, qy) in zip(tf, truth):
        px -= tf_mean[0]
        py -= tf_mean[1]
        qx -= truth_mean[0]
        qy -= truth_mean[1]
        cross += px * qy - py * qx
        dot += px * qx + py * qy
    yaw = math.atan2(cross, dot)
    c, s = math.cos(yaw), math.sin(yaw)
    dx = truth_mean[0] - (c * tf_mean[0] - s * tf_mean[1])
    dy = truth_mean[1] - (s * tf_mean[0] + c * tf_mean[1])
    return dx, dy, yaw


def transform(point, fit):
    dx, dy, yaw = fit
    c, s = math.cos(yaw), math.sin(yaw)
    return (c * point[0] - s * point[1] + dx,
            s * point[0] + c * point[1] + dy)


def errors(rows, fit=None):
    values = []
    for row in rows:
        tf = (float(row["tf_x"]), float(row["tf_y"]))
        if fit is not None:
            tf = transform(tf, fit)
        truth = (float(row["truth_x"]), float(row["truth_y"]))
        values.append(math.hypot(tf[0] - truth[0], tf[1] - truth[1]))
    return values


def load_map(run_dir):
    config = {}
    for line in (run_dir / "map.yaml").read_text().splitlines():
        if ":" not in line:
            continue
        key, value = line.split(":", 1)
        config[key.strip()] = value.strip().strip("'\"")
    origin = [float(value) for value in config["origin"].strip("[]").split(",")]
    image = mpimg.imread(run_dir / config["image"])
    return image, float(config["resolution"]), origin


def plot_alignment(name, run_dir, output, rows, fit):
    image, resolution, origin = load_map(run_dir)
    height, width = image.shape[:2]
    extent = (origin[0], origin[0] + width * resolution,
              origin[1], origin[1] + height * resolution)
    tf = [(float(row["tf_x"]), float(row["tf_y"])) for row in rows]
    truth = [(float(row["truth_x"]), float(row["truth_y"])) for row in rows]
    aligned = [transform(point, fit) for point in tf]
    figure, axis = plt.subplots(figsize=(9, 7), dpi=150)
    axis.imshow(image, cmap="gray", origin="lower", extent=extent, alpha=0.72)
    axis.plot(*zip(*truth), color="#111111", linewidth=1.15,
              label="Gazebo truth", zorder=4)
    axis.plot(*zip(*tf), color="#d62728", linewidth=0.75, alpha=0.65,
              linestyle="--", label="TF raw", zorder=3)
    axis.plot(*zip(*aligned), color="#1f77b4", linewidth=0.8, alpha=0.75,
              label="TF after fitted SE(2)", zorder=3)
    stride = max(1, len(rows) // 40)
    for index in range(0, len(rows), stride):
        axis.plot((tf[index][0], truth[index][0]),
                  (tf[index][1], truth[index][1]),
                  color="#ff9896", linewidth=0.35, alpha=0.55, zorder=2)
    axis.scatter([truth[0][0]], [truth[0][1]], color="#2ca02c", s=22,
                 label="start", zorder=5)
    axis.scatter([truth[-1][0]], [truth[-1][1]], color="#9467bd", s=22,
                 label="end", zorder=5)
    axis.set_title(
        f"{name}: map-frame TF/truth alignment; "
        f"fit dx={fit[0]:.4g}, dy={fit[1]:.4g}, yaw={math.degrees(fit[2]):.4g} deg")
    axis.set_xlabel("map x [m]")
    axis.set_ylabel("map y [m]")
    axis.set_aspect("equal", adjustable="box")
    axis.legend(fontsize=7, loc="best", ncol=2)
    figure.tight_layout()
    figure.savefig(output / f"coordinate-alignment-{name}.png")
    plt.close(figure)


def analyze(name, run_dir, output):
    rows = read_csv(run_dir / "pose-comparison.csv")
    rows = [row for row in rows if row.get("tf_x") and row.get("truth_x")]
    fit = fit_se2(rows)
    raw = errors(rows)
    aligned = errors(rows, fit)
    stamps = [int(row["stamp_ns"]) for row in rows]
    intervals = [(b - a) / 1e9 for a, b in zip(stamps, stamps[1:])]
    plot_alignment(name, run_dir, output, rows, fit)
    return {
        "scene": name,
        "samples": len(rows),
        "first_stamp_ns": stamps[0],
        "last_stamp_ns": stamps[-1],
        "monotonic_timestamps": all(b >= a for a, b in zip(stamps, stamps[1:])),
        "median_dt_s": f"{median(intervals):.6f}",
        "fit_dx_m": f"{fit[0]:.9f}",
        "fit_dy_m": f"{fit[1]:.9f}",
        "fit_yaw_deg": f"{math.degrees(fit[2]):.9f}",
        "raw_median_error_m": f"{median(raw):.9f}",
        "raw_p95_error_m": f"{percentile(raw, .95):.9f}",
        "raw_max_error_m": f"{max(raw):.9f}",
        "aligned_median_error_m": f"{median(aligned):.9f}",
        "aligned_p95_error_m": f"{percentile(aligned, .95):.9f}",
        "aligned_max_error_m": f"{max(aligned):.9f}",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--results", type=Path, default=Path("results/coverage-direct-20261116"))
    args = parser.parse_args()
    output = args.results / "analysis"
    output.mkdir(parents=True, exist_ok=True)
    rows = []
    all_pose_rows = []
    for name, relative in RUNS.items():
        run_dir = args.results / relative
        scene_row = analyze(name, run_dir, output)
        rows.append(scene_row)
        pose_rows = read_csv(run_dir / "pose-comparison.csv")
        all_pose_rows.extend(row for row in pose_rows if row.get("tf_x") and row.get("truth_x"))

    global_fit = fit_se2(all_pose_rows)
    raw = errors(all_pose_rows)
    aligned = errors(all_pose_rows, global_fit)
    global_row = {
        "scene": "all_scenes",
        "samples": len(all_pose_rows),
        "first_stamp_ns": "",
        "last_stamp_ns": "",
        "monotonic_timestamps": "",
        "median_dt_s": "",
        "fit_dx_m": f"{global_fit[0]:.9f}",
        "fit_dy_m": f"{global_fit[1]:.9f}",
        "fit_yaw_deg": f"{math.degrees(global_fit[2]):.9f}",
        "raw_median_error_m": f"{median(raw):.9f}",
        "raw_p95_error_m": f"{percentile(raw, .95):.9f}",
        "raw_max_error_m": f"{max(raw):.9f}",
        "aligned_median_error_m": f"{median(aligned):.9f}",
        "aligned_p95_error_m": f"{percentile(aligned, .95):.9f}",
        "aligned_max_error_m": f"{max(aligned):.9f}",
    }
    fields = list(rows[0])
    with (output / "coordinate-alignment.csv").open("w", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows + [global_row])

    report = [
        "# Coordinate and Timestamp Alignment",
        "",
        "The benchmark records coverage waypoints and Nav2 global plans in `map`.",
        "Gazebo truth is published with `header.frame_id=map`; its node applies a",
        "startup SE(2) offset from the odometry source to the configured spawn pose.",
        "The pose comparison uses each truth message timestamp to query",
        "`map <- base_footprint`, so the two pose columns are compared at matching",
        "simulation timestamps in the same frame.",
        "",
        "This report independently fits `truth ~= R(tf) + t`. A fitted transform",
        "near identity, combined with unchanged residuals, rules out a fixed",
        "world/map or map/odom translation/rotation as the source of the observed",
        "centimetre-scale residuals. It does not claim that all TF error is zero:",
        "the remaining residual includes timestamp interpolation, TF publication",
        "latency and controller/localization error.",
        "",
        "The original report's 0.035--0.040 values are metres, not metres times",
        "100; they correspond to approximately 3.5--4.0 centimetres.",
        "",
        "See `coordinate-alignment.csv` and the five `coordinate-alignment-*.png`",
        "plots for per-scene fit parameters and visual overlay checks.",
    ]
    (output / "coordinate-alignment.md").write_text("\n".join(report) + "\n")


if __name__ == "__main__":
    main()
