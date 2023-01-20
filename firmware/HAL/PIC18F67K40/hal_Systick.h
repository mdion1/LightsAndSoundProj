#include <stdint.h>
#include <stdbool.h>

void hal_SystickInit(void);
void hal_SystickDelay(uint16_t delay);
uint16_t hal_Systick32Upper(void);
uint32_t hal_Systick32(void);
uint16_t hal_Systick16(void);