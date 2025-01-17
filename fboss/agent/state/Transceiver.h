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

#include "fboss/agent/Utils.h"
#include "fboss/agent/gen-cpp2/switch_state_types.h"
#include "fboss/agent/state/NodeBase.h"
#include "fboss/agent/state/Thrifty.h"
#include "fboss/agent/types.h"
#include "fboss/qsfp_service/if/gen-cpp2/transceiver_types.h"

#include <optional>

namespace facebook::fboss {

struct TransceiverSpecFields : public ThriftyFields<
                                   TransceiverSpecFields,
                                   state::TransceiverSpecFields> {
  explicit TransceiverSpecFields(TransceiverID id) {
    auto& data = writableData();
    *data.id() = id;
  }

  bool operator==(const TransceiverSpecFields& other) const {
    return data() == other.data();
  }

  template <typename Fn>
  void forEachChild(Fn /*fn*/) {}

  state::TransceiverSpecFields toThrift() const override;
  static TransceiverSpecFields fromThrift(
      state::TransceiverSpecFields const& tcvrThrift);
  static folly::dynamic migrateToThrifty(folly::dynamic const& dyn);
  static void migrateFromThrifty(folly::dynamic& dyn);
  folly::dynamic toFollyDynamicLegacy() const;
  static TransceiverSpecFields fromFollyDynamicLegacy(
      const folly::dynamic& tcvrJson);
};

/*
 * TransceiverSpec stores state about one of the Present TransceiverSpec entries
 * on the switch. Mainly use it as a reference to program Port.
 */
class TransceiverSpec : public ThriftyBaseT<
                            state::TransceiverSpecFields,
                            TransceiverSpec,
                            TransceiverSpecFields> {
 public:
  explicit TransceiverSpec(TransceiverID id);
  static std::shared_ptr<TransceiverSpec> createPresentTransceiver(
      const TransceiverInfo& tcvrInfo);

  cfg::PlatformPortConfigOverrideFactor toPlatformPortConfigOverrideFactor()
      const;

  TransceiverID getID() const {
    return TransceiverID(*getFields()->data().id());
  }

  std::optional<double> getCableLength() const {
    return getFields()->data().cableLength().to_optional();
  }
  void setCableLength(double cableLength) {
    writableFields()->writableData().cableLength() = cableLength;
  }

  std::optional<MediaInterfaceCode> getMediaInterface() const {
    return getFields()->data().mediaInterface().to_optional();
  }
  void setMediaInterface(MediaInterfaceCode mediaInterface) {
    writableFields()->writableData().mediaInterface() = mediaInterface;
  }

  std::optional<TransceiverManagementInterface> getManagementInterface() const {
    return getFields()->data().managementInterface().to_optional();
  }
  void setManagementInterface(
      TransceiverManagementInterface managementInterface) {
    writableFields()->writableData().managementInterface() =
        managementInterface;
  }

  bool operator==(const TransceiverSpec& tcvr) const;
  bool operator!=(const TransceiverSpec& tcvr) const {
    return !(*this == tcvr);
  }

 private:
  // Inherit the constructors required for clone()
  using ThriftyBaseT<
      state::TransceiverSpecFields,
      TransceiverSpec,
      TransceiverSpecFields>::ThriftyBaseT;
  friend class CloneAllocator;
};
} // namespace facebook::fboss
