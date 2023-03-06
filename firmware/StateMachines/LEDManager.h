#pragma once
#include <stdint.h>
#include <stdbool.h>

void LEDMgr_init(void);
void LEDMgr_disable(void);  // turns off LED's and disables PWM module
void LEDMgr_enable(void);   // Resets state machine on enable
void LEDMgr_tasks(void);