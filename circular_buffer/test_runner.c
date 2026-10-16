#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer) {
  RUN_TEST_CASE(CircularBuffer, CorrectSizeConstructed);
  RUN_TEST_CASE(CircularBuffer, ErrorOnEmptyBufferGet);
  RUN_TEST_CASE(CircularBuffer, GetGivesTheSameValueAsPut);
  RUN_TEST_CASE(CircularBuffer, CreatedWithAvailableSpaceEqualToSize);
  RUN_TEST_CASE(CircularBuffer, NotNullConstructed);
}
