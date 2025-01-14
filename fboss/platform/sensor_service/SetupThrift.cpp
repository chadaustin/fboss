/*
 *  Copyright (c) 2004-present, Meta Platforms, Inc. and affiliates.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "fboss/platform/sensor_service/SetupThrift.h"

#include "thrift/lib/cpp2/server/ThriftServer.h"

#include "fboss/platform/helpers/Init.h"
#include "fboss/platform/sensor_service/SensorServiceImpl.h"
#include "fboss/platform/sensor_service/SensorServiceThriftHandler.h"

DEFINE_int32(thrift_port, 5970, "Port for the thrift service");

DEFINE_string(
    config_path,
    "",
    "Optional platform Sensor Configuration File Path. If empty we pick the platform default config");

namespace facebook::fboss::platform::sensor_service {

std::pair<
    std::shared_ptr<apache::thrift::ThriftServer>,
    std::shared_ptr<SensorServiceThriftHandler>>
setupThrift() {
  // Init SensorService
  std::shared_ptr<SensorServiceImpl> sensorService =
      std::make_shared<SensorServiceImpl>(FLAGS_config_path);

  // Fetch sensor data once to warmup
  sensorService->fetchSensorData();

  return helpers::setupThrift<SensorServiceThriftHandler>(
      sensorService, FLAGS_thrift_port);
}
} // namespace facebook::fboss::platform::sensor_service
