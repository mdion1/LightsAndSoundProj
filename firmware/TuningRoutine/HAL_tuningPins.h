#pragma once
#include <stdint.h>
#include <stdbool.h>

void Pins_tearDownTuningMode(void);
bool Pins_getTriggerState(void);    // returns true if trigger is held low (active)
void Pins_setupTuningMode(void);