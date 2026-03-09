cmake_minimum_required(VERSION 3.8)
project(aruco_tracker)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)

# Create executable
add_executable(aruco_tracker_node 
  ArucoTracker.cpp
)

target_include_directories(aruco_tracker_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OpenCV_INCLUDE_DIRS}
)

target_compile_features(aruco_tracker_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

ament_target_dependencies(aruco_tracker_node
  rclcpp
  sensor_msgs
  geometry_msgs
  cv_bridge
  image_transport
)

target_link_libraries(aruco_tracker_node ${OpenCV_LIBS})

# Install executable
install(TARGETS aruco_tracker_node
  DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# Install config files
install(DIRECTORY
  cfg
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()