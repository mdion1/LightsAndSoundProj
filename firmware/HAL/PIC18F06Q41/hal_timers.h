#pragma once
#include <stdint.h>
#include <stdbool.h>

/** Timer allocation
 *
 * Timer0: Sleep timer, used to wake the system up to poll audio signal
 * Timer1: Systick clock
 * Timer2: ADC sampling trigger
 * Timer3: unused
 * Timer4: unused
 */