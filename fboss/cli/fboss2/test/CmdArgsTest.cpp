// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include <fboss/cli/fboss2/utils/CmdUtils.h>
#include "fboss/cli/fboss2/CmdHandler.h"

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

using namespace ::testing;

namespace facebook::fboss {
namespace {

std::vector<std::string> getPortList() {
  return {"eth1/1/1", "eth1/20/3", "eth1/32/4"};
}

std::vector<std::string> getPrbsComponent() {
  return {
      "asic",
      "xphy_system",
      "xphy_line",
      "transceiver_system",
      "transceiver_line"};
}

utils::PortList doTypingImplicitPortList() {
  return getPortList();
}

utils::PrbsComponent doTypingImplicitPrbsComponent() {
  return getPrbsComponent();
}

std::tuple<utils::PortList, utils::PrbsComponent> doTypingImplicitTuple() {
  return std::make_tuple(getPortList(), getPrbsComponent());
}

template <typename TypedArgs, typename UnTypedArgs>
TypedArgs doTyping(UnTypedArgs& unTypedArgs) {
  return unTypedArgs;
}

} // namespace

TEST(CmdArgsTest, doTypingImplicitSingle) {
  auto typedPortList = doTypingImplicitPortList();
  auto typedPrbsComponent = doTypingImplicitPrbsComponent();
  EXPECT_EQ(typeid(typedPortList), typeid(utils::PortList));
  EXPECT_EQ(typeid(typedPrbsComponent), typeid(utils::PrbsComponent));
  static_assert(std::is_same_v<utils::PortList, decltype(typedPortList)>);
  static_assert(
      std::is_same_v<utils::PrbsComponent, decltype(typedPrbsComponent)>);
}

TEST(CmdArgsTest, doTypingImplicitTuple) {
  auto typedArgs = doTypingImplicitTuple();
  static_assert(std::is_same_v<
                utils::PortList,
                std::tuple_element_t<0, decltype(typedArgs)>>);
  static_assert(std::is_same_v<
                utils::PrbsComponent,
                std::tuple_element_t<1, decltype(typedArgs)>>);
}

TEST(CmdArgsTest, doTypingTemplating) {
  using TypedArgsTest = std::tuple<utils::PortList, utils::PrbsComponent>;
  auto untypedArgs = std::make_tuple(getPortList(), getPrbsComponent());
  auto typedArgs = doTyping<TypedArgsTest>(untypedArgs);
  static_assert(std::is_same_v<
                utils::PortList,
                std::tuple_element_t<0, decltype(typedArgs)>>);
  static_assert(std::is_same_v<
                utils::PrbsComponent,
                std::tuple_element_t<1, decltype(typedArgs)>>);
}

} // namespace facebook::fboss