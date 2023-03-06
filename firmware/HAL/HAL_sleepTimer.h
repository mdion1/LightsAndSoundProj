#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    SLEEP_INT_AFESTAGE_POWERUP = -1,
    SLEEP_INT_MIN = 0,
    SLEEP_INT_1,
    SLEEP_INT_2,
    SLEEP_INT_3,
    SLEEP_INT_4,
    SLEEP_INT_5,
    SLEEP_INT_6,
    SLEEP_INT_7,
    SLEEP_INT_MAX,
}SleepTimerInt_t;

void HAL_sleepTimerInit(void);
void HAL_sleepTimerSetInterval(SleepTimerInt_t interval);
void HAL_SleepTimerEnable(bool en);