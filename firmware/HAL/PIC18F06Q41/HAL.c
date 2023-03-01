#ifdef __PIC18F06Q41__
#include "../HAL.h"
#include <xc.h>
#include "hal_ADC.h"
#include "hal_interrupts.h"
#include "hal_PWM.h"
#include "hal_timers.h"

/* Board */
void HAL_initBoard()
{
    /* Set Peripheral Module Disable bit for all modules */
    PMD0 = 0xff;    // Disable FOSC, FVR, HLVD, CRC, SCAN, CLKR, IOC
    PMD1 = 0xff;    // Disable C1, ZCD, SMT1, Timers 0 - 4
    PMD2 = 0xff;    // Disable CCP1, CWG1, DSM1, NCO1, ACT, DAC1, ADC, C2
    PMD3 = 0xff;    // Disable UART1 and 2; SPI1 and 2; I2C1; PWM 1, 2, and 3
    PMD4 = 0xff;    // Disable DMA 1, 2, 3; CLC 1, 2, 3, 4; UART0
    PMD5 = 0xff;    // Disable OPA1, DAC2, DMA0;
    
    /* Set all pins to digital outputs, set low. */
    LATA = 0;
    LATC = 0;
    ANSELA = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISC = 0;
    
    PWM_config();
    TMR_configTMR2(TSAMP_PRESCALER, TSAMP_POSTSCALER, TSAMP_PERIOD);
}

void HAL_EnAmpStage()
{
    LATA = (1 << 2);
}

void HAL_DisAmpStage()
{
    LATA &= ~(1 << 2);
}

void prepForSleep()
{

}

/* ADC */
void HAL_ADCEnable()
{
    //enable ADC, enable interrupts, enable timer
    
}

void HAL_ADCDisable()
{
    //disable ADC, disable interrupts, disable timer
}

int16_t HAL_ADCReadInternalTemp()
{
    //todo
}

int16_t HAL_ADCGetConv()
{
    return ADC_getConv();
}

bool HAL_ADCIsEnabled()
{
    
}

/* Interrupts */
void HAL_registerADCisr(void (*p_callback)(void))
{
    INT_registerADCISRCallback(p_callback);
}

void HAL_registerSleepTimerISR(void (*p_callback)(void))
{
    INT_resisterTMR0ISRCallback(p_callback);
}

/* Sleep */
void HAL_setWakeOnTimer(uint8_t timerPeriod)    /*! \todo timerPeriod is unused */
{
    /* Enable TMR0 + interrupts */
    INT_clrTMR0IntFlag();
    INT_EnTMR0Int(true);
    TMR_EnTMR0();
}

void HAL_setWakeOnADC()
{
    INT_EnADCInt(true);
}

void HAL_sleep()
{
    /* Prep for sleep by turning off extraneous modules */
    HAL_DisAmpStage();
    PWM_dis();
    TMR_DisTMR1();      // Systick timer
    
    SLEEP();
    NOP();      // instruction following SLEEP must be NOP
}

/* PWM */
void HAL_enablePWM() {
    PWM_en();
}

void HAL_disablePWM() {
    PWM_dis();
}

void HAL_setPWM(uint8_t R, uint8_t G, uint8_t B) {
    PWM_setVals(R, G, B);
}

#endif