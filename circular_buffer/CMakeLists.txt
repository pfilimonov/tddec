add_executable(circular_buffer_test)

target_sources(circular_buffer_test
  PRIVATE
    test_circular_buffer.c
    test_runner.c
    all_tests.c
    circular_buffer.c

  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS
    .
  FILES
    ./circular_buffer.h 
)

target_link_libraries(circular_buffer_test
  PRIVATE
    project_warnings
    Unity
)
