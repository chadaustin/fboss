/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#pragma once

#include "fboss/agent/HwSwitch.h"

namespace facebook::fboss::utility {

// Gets the PFC enabled/disabled status for RX/TX from HW
void getPfcEnabledStatus(
    const HwSwitch* hw,
    const PortID& portId,
    bool& pfcRx,
    bool& pfcTx);

// Verifies if the PFC watchdog config provided matches the one
// programmed in BCM HW
void pfcWatchdogProgrammingMatchesConfig(
    const HwSwitch* hw,
    const PortID& portId,
    const bool watchdogEnabled,
    const cfg::PfcWatchdog& watchdog);

} // namespace facebook::fboss::utility