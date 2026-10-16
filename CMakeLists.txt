cmake_minimum_required(VERSION 3.23)

project(tddec)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)

# Unity
add_library(Unity)
target_sources(Unity
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity.c
  ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity_fixture.c
  ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity_memory.c

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/unity/
    FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity.h
      ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity_internals.h
      ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity_fixture.h
      ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity_fixture_internals.h
      ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity_memory.h
)

# CppUTest
find_package(CppUTest)

add_subdirectory(ch2)

