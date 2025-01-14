/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include "fboss/agent/hw/test/HwTestPfcUtils.h"
#include <gtest/gtest.h>

namespace facebook::fboss::utility {

// Gets the PFC enabled/disabled status for RX/TX from HW
void getPfcEnabledStatus(
    const HwSwitch* /* unused */,
    const PortID& /* unused */,
    bool& /* unused */,
    bool& /* unused */) {
  // This function is not implemented yet.
  // If the test is running on SAI Switches,
  // it should throw an error.
  EXPECT_TRUE(false);
}

// Verifies if the PFC watchdog config provided matches the one
// programmed in BCM HW
void pfcWatchdogProgrammingMatchesConfig(
    const HwSwitch* /* unused */,
    const PortID& /* unused */,
    const bool /* unused */,
    const cfg::PfcWatchdog& /* unused */) {
  // This function is not implemented yet.
  // If the test is running on SAI Switches,
  // it should throw an error.
  EXPECT_TRUE(false);
}

int getPfcDeadlockDetectionTimerGranularity(int /* unused */) {
  EXPECT_TRUE(false);
  // This function is not implemented yet.
  // If the test is running on SAI Switches,
  // it should throw an error.
  return 0;
}

int getCosqPFCDeadlockTimerGranularity() {
  EXPECT_TRUE(false);
  return 0;
}

int getProgrammedPfcWatchdogControlParam(
    const HwSwitch* /* unused */,
    const PortID& /* unused */,
    int /* unused */) {
  // This function is not implemented yet.
  // If the test is running on SAI Switches,
  // it should throw an error.
  EXPECT_TRUE(false);
  return 0;
}

int getPfcWatchdogRecoveryAction() {
  // This function is not implemented yet.
  // If the test is running on SAI Switches,
  // it should throw an error.
  EXPECT_TRUE(false);
  return -1;
}

// Maps cfg::PfcWatchdogRecoveryAction to SAI specific value
int pfcWatchdogRecoveryAction(cfg::PfcWatchdogRecoveryAction /* unused */) {
  // This function is not implemented yet.
  // If the test is running on SAI Switches,
  // it should throw an error.
  EXPECT_TRUE(false);
  return 0;
}

} // namespace facebook::fboss::utility
