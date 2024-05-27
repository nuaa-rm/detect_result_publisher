cmake_minimum_required(VERSION 3.8)
project(detect_result_publisher)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies


find_package(ament_cmake_auto REQUIRED)
find_package(detector_interfaces REQUIRED)
include_directories(
        include
        ${detector_interfaces_INCLUDE_DIRS}
)
#find_package(detector_interfaces REQUIRED)
ament_auto_find_build_dependencies()
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

ament_auto_add_executable(detect_result_publisher_node src/detect_result_publisher_node.cpp
        src/detect_result_publisher.cpp
        include/detect_result_publisher.h
        include/robot.h
        src/robot.cpp
)
target_compile_features(detect_result_publisher_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
