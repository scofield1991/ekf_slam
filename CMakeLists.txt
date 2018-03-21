project(ekfslam)
cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(PythonLibs 2.7)
include_directories(${PYTHON_INCLUDE_DIRS})

# Eigen
include_directories( "/usr/include/eigen3" )

add_executable(ekf_slam src/main.cpp src/ekf.cpp)
#target_include_directories(ekf_slam ${PYTHON_INCLUDE_DIRS})
target_link_libraries(ekf_slam ${PYTHON_LIBRARIES})