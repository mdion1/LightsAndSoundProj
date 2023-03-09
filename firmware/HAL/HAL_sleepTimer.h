#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    SLEEP_INT_AFESTAGE_POWERUP = 0,
    SLEEP_INT_MIN = 1,
    SLEEP_INT_1 = 1,
    SLEEP_INT_2 = 2,
    SLEEP_INT_3 = 3,
    SLEEP_INT_4 = 4,
    SLEEP_INT_5 = 5,
    SLEEP_INT_6 = 6,
    SLEEP_INT_7 = 7,
    SLEEP_INT_MAX = 7,
}SleepTimerInt_t;

void HAL_sleepTimerInit(void);
void HAL_sleepTimerSetInterval(SleepTimerInt_t interval);
void HAL_sleepTimerStart(void);
void HAL_SleepTimerEnable(bool en);