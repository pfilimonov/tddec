add_executable(ExampleUnity)

target_sources(ExampleUnity
  PRIVATE
    test_sprintf_unity.c
    test_sprintf_unity_runner.c
    all_tests_unity.c
)

target_link_libraries(ExampleUnity
  PRIVATE
    Unity
)

add_executable(ExampleCppUTest)

target_sources(ExampleCppUTest
  PRIVATE
    test_sprintf_cpputest.cpp
    all_tests_cpputest.cpp
)

target_link_libraries(ExampleCppUTest
  PRIVATE
    CppUTest
)
