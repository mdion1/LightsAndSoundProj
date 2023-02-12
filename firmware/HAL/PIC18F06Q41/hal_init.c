

void initBoard()
{
    /* Set all pins to digital outputs, set low. */
    LATA = 0;
    LATC = 0;
    ANSELA = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISC = 0;
    
    /* Set analog input */
    
}

void initOtherStuff() {
    
    /* Peripheral module disable */
    PMD0 = 0xff;    // Disable FOSC, FVR, HLVD, CRC, SCAN, CLKR, IOC
    PMD1 = 0xff;    // Disable C1, ZCD, SMT1, Timers 0 - 4
    PMD2 = 0xff;    // Disable CCP1, CWG1, DSM1, NCO1, ACT, DAC1, ADC, C2
    PMD3 = 0xff;    // Disable UART1 and 2; SPI1 and 2; I2C1; PWM 1, 2, and 3
    PMD4 = 0xff;    // Disable DMA 1, 2, 3; CLC 1, 2, 3, 4; UART0
    PMD5 = 0xff;    // Disable OPA1, DAC2, DMA0;
    
    // Enable ADC
    PDM2 &= 0b11111101;
    
    // Disable ADC
    PMD2 |= 0b00000010;
}

void clampAnalogInput()
{
    TRISA &= ~(1 << 5);
    ANSELA &= ~(1 << 5);
    TRISA |= (1 << 5);      // set pin high
}

void setAnalogInput()
{
    TRISA |= (1 << 5);
    ANSELA |= (1 << 5);
}

void turnOnAFE()
{
    LATA = (1 << 2);
}

void turnOffAFE()
{
    LATA &= ~(1 << 2);
}

void prepForSleep()
{
    turnOffAFE();
    
    disablePWM();
    Timer1Disable();
    
    // Sleep timer
    Timer0Enable();
    
    
}