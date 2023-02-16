#ifdef __PIC18F06Q41__
#pragma once
#include <stdint.h>
#include <stdbool.h>

void ADC_init();
void ADC_En();
void ADC_Dis();
//void HAL_ADCInit_single();
bool ADC_isBusy();
int16_t ADC_getConv();

#endif