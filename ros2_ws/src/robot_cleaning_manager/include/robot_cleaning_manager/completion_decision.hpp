// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <algorithm>
#include <string>

namespace robot_cleaning_manager
{
struct CompletionDecision
{
  bool finish{false};
  bool success{false};
  std::string reason;
};

inline CompletionDecision decide_completion(
  double coverage, double target, double margin, bool gap_budget_exhausted)
{
  if (coverage >= std::min(1.0, target + margin)) {
    return {true, true, "Coverage target reached with completion margin"};
  }
  if (!gap_budget_exhausted) {
    return {};
  }
  if (coverage >= target) {
    return {true, true,
      "Coverage target reached; completion margin not reached within gap-fill limit"};
  }
  return {true, false, "Coverage target not reached; gap-fill limit exhausted"};
}
}  // namespace robot_cleaning_manager
