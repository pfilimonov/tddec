#include "unity_fixture.h"

TEST_GROUP_RUNNER(LedDriver) {
  RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
  RUN_TEST_CASE(LedDriver, TurnOnLedOne);
  RUN_TEST_CASE(LedDriver, TurnOffLedOne);
  RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
  RUN_TEST_CASE(LedDriver, AllOn);
  RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
  RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
  RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
  RUN_TEST_CASE(LedDriver, OutOfBoundsOnChangesNothing);
  RUN_TEST_CASE(LedDriver, OutOfBoundsOffChangesNothing);
  RUN_TEST_CASE(LedDriver, OutOfBoundsOnProducesRuntimeError);
  RUN_TEST_CASE(LedDriver, OutOfBoundsOffProducesRuntimeError);
  RUN_TEST_CASE(LedDriver, IsOn);
  RUN_TEST_CASE(LedDriver, OutOfBoundsLedsAreAlwaysNotOn);
  RUN_TEST_CASE(LedDriver, IsOff);
  RUN_TEST_CASE(LedDriver, OutOfBoundsLedsAreAlwaysOff);
  RUN_TEST_CASE(LedDriver, TurnOffMultipleLeds);
  RUN_TEST_CASE(LedDriver, AllOff);
}
