#pragma once

/* Peripheral module disable registers */
#include <stdint.h>
#include <stdbool.h>

void HAL_PMD_disAll(void);
void HAL_PMD_enADC(bool en);
void HAL_PMD_enPWM(bool en);
void HAL_PMD_enTMR(bool en, uint8_t timer);