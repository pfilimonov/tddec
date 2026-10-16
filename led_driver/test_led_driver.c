#include "led_driver.h"
#include "unity.h"
#include "unity_fixture.h"
#include <stdint.h>

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver) { LedDriver_Create(&virtualLeds); }
TEST_TEAR_DOWN(LedDriver) {}

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
