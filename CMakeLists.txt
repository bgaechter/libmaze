cmake_minimum_required(VERSION 3.21)
project(libmaze CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "The configuration to build" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
option(BUILD_UNIT_TESTS "Build unit tests" ON)

add_subdirectory(src)


if(${BUILD_UNIT_TESTS})
	enable_testing()
  add_subdirectory(test)
endif()
