#include "SignalSampling.h"
#include "SamplingParams.h"

/* Private variable declarations */
#define SAMP_GRPSIZ_MASK RELATIVE_FSAMP

// List of states
typedef enum {
    IDLE = 0,
    SAMPLING = 1
}SigSampState_t;

// State machine owned by the main software thread
static struct {
    SigSampState_t state;
    uint16_t headIdxCpy;             //buffer index of the next sample to be converted; copy of the volatile variable owned by the ISR, updated every task loop
}SM;

// State machine owned by the ISR
static volatile struct {
    uint16_t headIdx;            //buffer index of the next sample to be converted; read-only except by the ISR callback
    bool bSampComplete;
}ISRvars;

// Sample buffer
static int16_t sampBuf[SAMPLE_BUF_SIZE];

/* Private function declarations */
static void samplingTasks();
static void ISRcallback();

/* Public function definitions */

void SigSamp_init()
{
    SM.state = IDLE;
    SM.headIdxCpy = 0;
    ISRvars.headIdx = 0;
    ISRvars.bSampComplete = false;
    HAL_registerADCisr(ISRcallback);
}

void SigSamp_start()
{
    //todo: disable ADC timer interrupt, disable timer, clear flags
    
    
    SM.state = SAMPLING;
    
    // Reset indices
    SM.headIdxCpy = 0;
    ISRvars.headIdx = 0;
    ISRvars.bSampComplete = false;
    
    // todo: enable ADC timer interrupt, enable timer
    HAL_ADCStartContinuous();
}

void SigSamp_stop()
{
    HAL_ADCstop();
    SM.state = IDLE;
    
    //todo: disable ADC timer interrupt, disable timer, clear flags
}

void SigSamp_tasks()
{
    switch(SM.state)
    {
        default:
        case IDLE:
        break;
        case SAMPLING:
            samplingTasks();
        break;
    }
}

uint16_t SigSamp_getNumSamples()
{
    return SM.headIdxCpy;
}

const int16_t* SigSamp_getSampBuf()
{
    return sampBuf;
}

SigSamp_isActive()
{
    return SAMPLING == SM.state;
}

/* Private function definitions */
static void samplingTasks()
{
    // Protected section: copy ISR-owned volatile variables
    HAL_disableInt();
    SM.headIdxCpy = ISRvars.headIdx;
    bool bDone = ISRvars.bSampComplete;
    HAL_enableInt();

    if (bDone)
    {
        SM.state = IDLE;
    }
}

static void ISRcallback()
{
    // Push new sample to the buffer
    sampBuf[ISRvars.headIdx] = HAL_getADCconv();

    // Increment buf indx
    ISRvars.headIdx++;
    if (ISRvars.headIdx == SAMPLE_BUF_SIZE)
    {
        //stop sampling
        ISRvars.bSampComplete = true;
    }
}