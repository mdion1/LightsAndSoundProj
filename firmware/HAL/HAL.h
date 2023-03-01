#pragma once
#include "../StateMachines/SamplingParams.h"
#include <stdint.h>
#include <stdbool.h>

/* Board */
void HAL_initBoard();

/* ADC */
void HAL_ADCEnable();
void HAL_ADCDisable();
int16_t HAL_ADCReadInternalTemp();
int16_t HAL_ADCGetConv();
bool HAL_ADCIsEnabled();

/* Interrupts */
void HAL_registerADCisr(void (*p_callback)(void));
void HAL_registerTimer0isr(void (*p_callback)(void));

/* Sleep */
void HAL_setWakeOnTimer(uint8_t timerPeriod);
void HAL_setWakeOnADC();
void HAL_sleep();

/* PWM */
void HAL_enablePWM();
void HAL_disablePWM();
void HAL_setPWM(uint8_t R, uint8_t G, uint8_t B);

/* Systick */
uint16_t HAL_Systick();

/* Interrupts */
void HAL_globalIntEn();
void HAL_globalIntDis();