/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "fboss/agent/platforms/sai/SaiCloudRipperPlatform.h"

#include "fboss/agent/hw/switch_asics/EbroAsic.h"
#include "fboss/agent/platforms/common/cloud_ripper/CloudRipperPlatformMapping.h"

namespace facebook::fboss {

SaiCloudRipperPlatform::SaiCloudRipperPlatform(
    std::unique_ptr<PlatformProductInfo> productInfo,
    folly::MacAddress localMac)
    : SaiTajoPlatform(
          std::move(productInfo),
          std::make_unique<CloudRipperPlatformMapping>(),
          localMac) {
  asic_ = std::make_unique<EbroAsic>();
}

std::string SaiCloudRipperPlatform::getHwConfig() {
  return *config()->thrift.platform()->get_chip().get_asic().config();
}

HwAsic* SaiCloudRipperPlatform::getAsic() const {
  return asic_.get();
}

SaiCloudRipperPlatform::~SaiCloudRipperPlatform() {}

} // namespace facebook::fboss
