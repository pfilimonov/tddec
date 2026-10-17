#include "led_driver.h"
#include "runtime_error_stub.h"
#include "unity.h"
#include "unity_fixture.h"
#include <stdint.h>

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver) { LedDriver_Create(&virtualLeds); }
TEST_TEAR_DOWN(LedDriver) { RunTimeErrorStub_Reset(); }

TEST(LedDriver, LedsOffAfterCreate) {
  uint16_t virtualLedsNotNull = 0xffff;
  LedDriver_Create(&virtualLedsNotNull);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLedsNotNull);
}

TEST(LedDriver, TurnOnLedOne) {
  LedDriver_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds) {
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

TEST(LedDriver, AllOn) {
  LedDriver_TurnAllOn();
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable) {
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsOnChangesNothing) {
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsOffChangesNothing) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsOnProducesRuntimeError) {
  LedDriver_TurnOn(-1);
  TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
                           RunTimeErrorStub_GetLastError());
  TEST_ASSERT_EQUAL(-1, RunTimeErrorStub_GetLastParameter());
}

TEST(LedDriver, OutOfBoundsOffProducesRuntimeError) {
  LedDriver_TurnOff(-1);
  TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
                           RunTimeErrorStub_GetLastError());
  TEST_ASSERT_EQUAL(-1, RunTimeErrorStub_GetLastParameter());
}
TEST(LedDriver, IsOn) {
  TEST_ASSERT_FALSE(LedDriver_IsOn(11));
  LedDriver_TurnOn(11);
  TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysNotOn) {
  TEST_ASSERT_FALSE(LedDriver_IsOn(0));
  TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff) {
  LedDriver_TurnAllOn();
  TEST_ASSERT_FALSE(LedDriver_IsOff(11));
  LedDriver_TurnOff(11);
  TEST_ASSERT_TRUE(LedDriver_IsOff(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff) {
  LedDriver_TurnAllOn();
  TEST_ASSERT_TRUE(LedDriver_IsOff(0));
  TEST_ASSERT_TRUE(LedDriver_IsOff(17));
}
TEST(LedDriver, TurnOffMultipleLeds) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(9);
  LedDriver_TurnOff(8);
  TEST_ASSERT_EQUAL_HEX16((~0x180) & 0xffff, virtualLeds);
}

TEST(LedDriver, AllOff) {
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
