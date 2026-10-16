#include "led_driver.h"

static uint16_t *ledsAddress;

void LedDriver_Create(uint16_t *address) {
  ledsAddress = address;
  *ledsAddress = 0;
}

void LedDriver_TurnOn(int ledNumber) { *ledsAddress = (uint16_t)ledNumber; }
void LedDriver_TurnOff(int ledNumber) {
  *ledsAddress = 0;
  (void)ledNumber;
}
