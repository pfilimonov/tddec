#include "led_driver.h"
#include "runtime_error.h"
#include <stdbool.h>
#include <stdint.h>

static uint16_t *ledsAddress;
static uint16_t ledsImage;
static bool invertedLogic;
static LedOrder ledOrder;

enum { ALL_LEDS_ONE = ~0, ALL_LEDS_ZERO = ~ALL_LEDS_ONE };
enum { FIRST_LED = 1, LAST_LED = 16 };

static uint16_t convertLedNumberToBit(int ledNumber) {
  return (uint16_t)(1 << (ledNumber - 1));
}

static bool IsLedOutOfBounds(int ledNumber) {
  return (ledNumber < FIRST_LED) || (ledNumber > LAST_LED);
}

static int orderLedNumber(int ledNumber) {
  return ledOrder == NORMAL ? ledNumber : 17 - ledNumber;
}

static void updateHardware(void) { *ledsAddress = ledsImage; }

static void setLedImageBit(int ledNumber) {
  if (invertedLogic) {
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
  } else {
    ledsImage |= convertLedNumberToBit(ledNumber);
  }
}

static void clearLedImageBit(int ledNumber) {
  if (invertedLogic) {
    ledsImage |= convertLedNumberToBit(ledNumber);
  } else {
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
  }
}

void LedDriver_Create(uint16_t *address, bool inverted, LedOrder order) {
  ledOrder = order;
  invertedLogic = inverted;
  ledsAddress = address;
  ledsImage = (uint16_t)(invertedLogic ? ALL_LEDS_ONE : ALL_LEDS_ZERO);
  updateHardware();
}

void LedDriver_TurnOn(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber)) {
    RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
    return;
  }
  setLedImageBit(orderLedNumber(ledNumber));
  *ledsAddress = ledsImage;
}
void LedDriver_TurnOff(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber)) {
    RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
    return;
  }
  clearLedImageBit(orderLedNumber(ledNumber));
  updateHardware();
}

void LedDriver_TurnAllOn(void) {
  ledsImage = (uint16_t)(invertedLogic ? ALL_LEDS_ZERO : ALL_LEDS_ONE);
  updateHardware();
}

bool LedDriver_IsOn(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber)) {
    return false;
  }
  bool cand = ledsImage & (convertLedNumberToBit(orderLedNumber(ledNumber)));
  if (invertedLogic) {
    return !cand;
  } else {
    return cand;
  }
}

bool LedDriver_IsOff(int ledNumber) {
  if (IsLedOutOfBounds(ledNumber)) {
    return true;
  }
  bool cand = ledsImage & (convertLedNumberToBit(orderLedNumber(ledNumber)));
  if (invertedLogic) {
    return cand;
  } else {
    return !cand;
  }
}

void LedDriver_TurnAllOff(void) {
  ledsImage = (uint16_t)(invertedLogic ? ALL_LEDS_ONE : ALL_LEDS_ZERO);
  updateHardware();
}
