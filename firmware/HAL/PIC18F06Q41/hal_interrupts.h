#ifdef __PIC18F06Q41__
#pragma once
#include <stdint.h>
#include <stdbool.h>

/* ADC interrupts */
void INT_registerADCISRCallback(void (*p_callback)(void));
void INT_EnADCInt(bool b_en);
void INT_clrADCIntFlag();

/* Timer0 interrupts */
void INT_resisterTMR0ISRCallback(void (*p_callback)(void));
void INT_EnTMR0Int(bool b_en);
void INT_clrTMR0IntFlag();

/* Global interrupt enable/disable */
void INT_GlobalIntEn();
void INT_GlobalIntDis();

#endif