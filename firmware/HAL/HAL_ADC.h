#pragma once
#include <stdint.h>
#include <stdbool.h>

void HAL_initADC(uint8_t prescaler, uint8_t postscaler, uint8_t period);
void HAL_registerADCisrCallback(void (*p_callback)(void));
int16_t HAL_ADCGetConv();
void HAL_ADCEnable();
void HAL_ADCDisable();