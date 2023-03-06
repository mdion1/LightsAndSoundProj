#pragma once
#include "../StateMachines/SamplingParams.h"
#include <stdint.h>
#include <stdbool.h>

/* Board */
void HAL_initBoard(void);

/* ADC */
void HAL_ADCEnable(void);
void HAL_ADCDisable(void);
int16_t HAL_ADCReadInternalTemp(void);
int16_t HAL_ADCGetConv(void);
bool HAL_ADCIsEnabled(void);

/* Interrupts */
void HAL_registerADCisr(void (*p_callback)(void));
void HAL_registerTimer0isr(void (*p_callback)(void));
void HAL_clrTMR0IntFlag(void);

/* Sleep */
void HAL_setWakeOnTimer(uint8_t timerPeriod);
void HAL_setWakeOnADC(void);
void HAL_sleep(void);

/* GPIO */
void HAL_EnAmpStage();
void HAL_DisAmpStage();

/* PWM */
void HAL_enablePWM(void);
void HAL_disablePWM(void);
void HAL_setPWM(uint8_t R, uint8_t G, uint8_t B);

/* Systick */
uint16_t HAL_Systick(void);

/* Interrupts */
void HAL_globalIntEn(void);
void HAL_globalIntDis(void);