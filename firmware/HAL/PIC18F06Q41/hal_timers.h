#ifdef __PIC18F06Q41__
#pragma once

/** Timer allocation
 *
 * Timer0: Sleep timer, used to wake the system up to poll audio signal
 * Timer1: Systick clock
 * Timer2: ADC sampling trigger
 * Timer3: unused
 * Timer4: unused
 */

#include <stdint.h>
#include <stdbool.h>

void TMR_configTMR0();
void TMR_EnTMR0();
void TMR_DisTMR0();
void TMR_configTMR1();
void TMR_EnTMR1();
void TMR_DisTMR1();
uint16_t TMR_getTMR1Count();
void TMR_configTMR2(uin8t_t prescaler, uint8_t postscaler, uint8_t period);
void TMR_EnTMR2();
void TMR_DisTMR2();

#endif