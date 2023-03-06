#pragma once
#include <stdint.h>
#include <stdbool.h>

void HAL_initPWM(void);
void HAL_PWMEnable(bool en);
void HAL_setPWM(uint8_t Rval, uint8_t Gval, uint8_t Bval);