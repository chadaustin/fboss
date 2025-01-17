/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include <folly/Benchmark.h>
#include <unordered_set>

#include "fboss/lib/CommonFileUtils.h"
#include "fboss/qsfp_service/platforms/wedge/WedgeManager.h"
#include "fboss/qsfp_service/platforms/wedge/WedgeManagerInit.h"

namespace facebook::fboss {

std::unique_ptr<WedgeManager> setupForColdboot() {
  // Once we setup for cold boot, WedgeManager will always reload xphy firmware
  // when initExternalPhyMap() is called
  createDir(FLAGS_qsfp_service_volatile_dir);
  auto fd = createFile(TransceiverManager::forceColdBootFileName());
  close(fd);

  gflags::SetCommandLineOptionWithMode(
      "force_reload_gearbox_fw", "1", gflags::SET_FLAGS_DEFAULT);

  return createWedgeManager();
}

// This function will read one byte from the offset 0 on transceivers
// with the specified media type.
std::size_t ReadOneByte(MediaInterfaceCode mediaType) {
  folly::BenchmarkSuspender suspender;
  std::size_t iters = 0;
  auto wedgeMgr = setupForColdboot();
  wedgeMgr->init();

  for (int i = 0; i < wedgeMgr->getNumQsfpModules(); i++) {
    TransceiverID id(i);
    auto interface = wedgeMgr->getTransceiverInfo(id).moduleMediaInterface();

    if (interface.has_value() && interface.value() == mediaType) {
      std::unordered_set<TransceiverID> tcvr{id};
      std::map<int32_t, ReadResponse> response;
      std::unique_ptr<ReadRequest> request(new ReadRequest);
      TransceiverIOParameters param;

      request->ids() = {i};
      param.offset() = 0;
      param.length() = 1;
      request->parameter() = param;

      suspender.dismiss();
      wedgeMgr->readTransceiverRegister(response, std::move(request));
      suspender.rehire();
      iters++;
    }
  }

  return iters;
}

BENCHMARK_MULTI(ReadRegister_CR4_100G) {
  return ReadOneByte(MediaInterfaceCode::CR4_100G);
}

BENCHMARK_MULTI(ReadRegister_CWDM4_100G) {
  return ReadOneByte(MediaInterfaceCode::CWDM4_100G);
}

BENCHMARK_MULTI(ReadRegister_FR4_200G) {
  return ReadOneByte(MediaInterfaceCode::FR4_200G);
}

BENCHMARK_MULTI(ReadRegister_FR4_400G) {
  return ReadOneByte(MediaInterfaceCode::FR4_400G);
}

BENCHMARK_MULTI(ReadRegister_LR4_400G_10KM) {
  return ReadOneByte(MediaInterfaceCode::LR4_400G_10KM);
}

} // namespace facebook::fboss
