#include <stdbool.h>
#include <stdint.h>

typedef enum { NORMAL, REVERSED } LedOrder;

void LedDriver_Create(uint16_t *address, bool inverted, LedOrder order);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
void LedDriver_TurnAllOn(void);
bool LedDriver_IsOn(int ledNumber);
bool LedDriver_IsOff(int ledNumber);
void LedDriver_TurnAllOff(void);
