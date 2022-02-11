# Make to build libraries and binaries in fboss/platform/weutils

# In general, libraries and binaries in fboss/foo/bar are built by
# cmake/FooBar.cmake

add_library(sensor_service_lib
  fboss/platform/sensor_service/GetSensorConfig.cpp
  fboss/platform/sensor_service/MockSensorConfig.cpp
  fboss/platform/sensor_service/SensorServiceImpl.cpp
  fboss/platform/sensor_service/oss/DarwinSensorConfig.cpp
)

target_link_libraries(sensor_service_lib
  product_info
  platform_utils
  sensor_service_cpp2
  sensor_config_cpp2
  Folly::folly
  FBThrift::thriftcpp2
)
