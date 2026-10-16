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

# warnings
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
  -Wall -Wextra -Wpedantic
  -Wshadow -Wconversion -Wsign-conversion
  -Wcast-qual -Wcast-align
  -Wformat=2 -Wnull-dereference
  -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition
  -Wundef -Wredundant-decls
  -Werror
)

# CppUTest
find_package(CppUTest)

# subdirs
add_subdirectory(ch2)
add_subdirectory(led_driver)
add_subdirectory(circular_buffer)

