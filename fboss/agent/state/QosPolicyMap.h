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

#include "fboss/agent/gen-cpp2/switch_state_types.h"
#include "fboss/agent/state/NodeMap.h"
#include "fboss/agent/state/NodeMapDelta.h"
#include "fboss/agent/state/QosPolicy.h"
#include "fboss/agent/state/Thrifty.h"
#include "fboss/agent/types.h"

#include <memory>

namespace facebook::fboss {

using QosPolicyMapTraits = NodeMapTraits<std::string, QosPolicy>;

struct QosPolicyMapThriftTraits
    : public ThriftyNodeMapTraits<std::string, state::QosPolicyFields> {
  static inline const std::string& getThriftKeyName() {
    static const std::string _key = "name";
    return _key;
  }

  static const KeyType parseKey(const folly::dynamic& key) {
    return key.asString();
  }
};

class QosPolicyMap : public ThriftyNodeMapT<
                         QosPolicyMap,
                         QosPolicyMapTraits,
                         QosPolicyMapThriftTraits> {
 public:
  QosPolicyMap();
  ~QosPolicyMap() override;

  std::shared_ptr<QosPolicy> getQosPolicyIf(const std::string& name) const {
    return getNodeIf(name);
  }

  QosPolicyMap* modify(std::shared_ptr<SwitchState>* state);

 private:
  // Inherit the constructors required for clone()
  using ThriftyNodeMapT::ThriftyNodeMapT;
  friend class CloneAllocator;
};

using QosPolicyMapDelta = NodeMapDelta<QosPolicyMap>;

} // namespace facebook::fboss
