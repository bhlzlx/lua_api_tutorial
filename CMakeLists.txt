cmake_minimum_required( VERSION 3.20)

project(lua_api_tutorial)

set(TUTORIAL_ROOT ${CMAKE_SOURCE_DIR})

include(cmakeconf/compiler_conf.cmake)
include(cmakeconf/building_output.cmake)

add_subdirectory(samples)