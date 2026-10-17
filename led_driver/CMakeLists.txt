add_executable(LedDriverTest)

target_sources(LedDriverTest
  PRIVATE
    test_led_driver.c
    led_driver_test_runner.c
    all_tests.c

    led_driver.c
    runtime_error_stub.c

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      .
    FILES
      ./led_driver.h
      ./runtime_error.h
      ./runtime_error_stub.h
)

target_link_libraries(LedDriverTest
  PRIVATE
  Unity
  project_warnings
)
