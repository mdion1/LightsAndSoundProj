/* ADC */
void HAL_ADCInit_single();
void HAL_ADCInit_onInterval(uint8_t clkPrescaler, uint8_t channelSel);

/* Interrupts */
void HAL_registerADCisr(void (*p_callback)(void));
void HAL_registerTimer0isr(void (*p_callback)(void));