#ifdef __PIC18F06Q41__
#pragma once
#include <stdint.h>
#include <stdbool.h>

/** PWM allocation
 *
 * PWM1: Red (P1) and green (P2) LED drivers
 * PWM2: Blue (P1) LED driver
 * PWM3: unused
 */

void PWM_config();
void PWM_en();
void PWM_dis();
void PWM_setVals(uint8_t Rval, uint8_t Gval, uint8_t Bval);

#endif