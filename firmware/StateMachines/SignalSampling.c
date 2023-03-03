#include "SignalSampling.h"
#include "SamplingParams.h"
#include "HAL/HAL.h"

/* Private variable declarations */
#define SAMPLE_BUF_SIZE 256

// State machine owned by the main software thread
static struct {
    uint16_t headIdxCpy;             //buffer index of the next sample to be converted; copy of the volatile variable owned by the ISR, updated every task loop
}SM;

// State machine owned by the ISR
static volatile struct {
    uint16_t headIdx;            //buffer index of the next sample to be converted; read-only except by the ISR callback
}ISRvars;

// Sample buffer
static int16_t sampBuf[SAMPLE_BUF_SIZE];

/* Private function declarations */
static void resetBuf();
static void ISRcallback();

/* Public function definitions */

void SigSamp_init()
{
    resetBuf();
    HAL_registerADCisr(ISRcallback);
}

void SigSamp_start()
{
    resetBuf();
    
    // todo: enable ADC timer interrupt, enable timer
    HAL_ADCEnable();
}

void SigSamp_stop()
{
    HAL_ADCDisable();
    resetBuf();
}

void SigSamp_tasks()
{
    /* If timer-triggered ADC sampling is not enabled, enable it. */
    if (!HAL_ADCIsEnabled()) {
        SigSamp_start();
        return;
    }
    
    /* Protected section: make local copies of ISR-owned volatile variables. */
    HAL_globalIntDis();
    SM.headIdxCpy = ISRvars.headIdx;
    HAL_globalIntEn();
}

uint8_t SigSamp_getNumSamples()
{
    return SM.headIdxCpy;
}

uint16_t SigSamp_getTimebase()
{
    /*! \todo document timebase theory/calculations */
    
}

const int16_t* SigSamp_getSampBuf()
{
    return sampBuf;
}

/* Private function definitions */
static void resetBuf()
{
    // Reset indices
    SM.headIdxCpy = 0;
    ISRvars.headIdx = 0;
}

static void ISRcallback()
{
    // Push new sample to the buffer
    sampBuf[ISRvars.headIdx] = HAL_ADCGetConv();

    // Increment buffer index
    ISRvars.headIdx++;
    if (SAMPLE_BUF_SIZE == ISRvars.headIdx) {   // headIdx must be an int16 to prevent rollover
        //stop sampling
        HAL_ADCDisable();
    }
}