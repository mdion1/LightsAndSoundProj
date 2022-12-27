#include "SignalSampling.h"
#include "SamplingParams.h"

/* Private variable declarations */

// List of states
typedef enum {
    IDLE = 0,
    SAMPLING = 1
}SigSampState_t;

// State machine owned by the main software thread
static struct {
    SigSampState_t state;
    int headIdxCpy;             //buffer index of the next sample to be converted; copy of the volatile variable owned by the ISR, updated every task loop
    int tailIdx;                //buffer index of the next sample to be processed; updated every task loop, set to the head index of the previous task loop
}SM;

// State machine owned by the ISR
static volatile struct {
    int headIdxVol;            //buffer index of the next sample to be converted; read-only except by the ISR callback
    bool b_collision;          // set only by the ISR callback; cleared by the main thread
}ISRvars;

// Sample buffer
static int16_t sampBuf[SAMPLE_BUF_SIZE];

/* Private function declarations */
static void resetBuf();
static void samplingTasks();
static void ISRcallback();

/* Public function definitions */

void SigSamp_init()
{
    SM.state = IDLE;
    resetBuf();

    //todo: register ISR callback
}

void SigSamp_start()
{
    HAL_ADCStartContinuous();
    SM.state = SAMPLING;
}

void SigSamp_stop()
{
    HAL_ADCstop();
    SM.state = IDLE;
}

SigSampEvents_t SigSamp_tasks()
{
    SigSampEvents_t events = (SigSampEvents_t) {
        .newSamples = 0,
        .buf = NULL
    };

    switch(SM.state)
    {
        default:
        case IDLE:
        break;
        case SAMPLING:
            samplingTasks();
            events.newSamples = SM.headIdxCpy - SM.tailIdx;
            events.buf = &sampBuf[SM.tailIdx];
        break;
    }

    return events;
}

/* Private function definitions */
static void resetBuf()
{
    SM.headIdxCpy = SM.tailIdx = 0;

    //critical section ("di"/"ei"), reset volatile ISR vars
}

static void samplingTasks()
{
    // Protected section: copy ISR-owned volatile variables
    HAL_disableInt();
    int headIdx_cpy = ISRvars.headIdxVol;
    bool collisionFlag = ISRvars.b_collision;
    HAL_enableInt();

    if (collisionFlag)
    {
        //todo: handle collision
        resetBuf();//??
    }
    else
    {
        SM.tailIdx = SM.headIdxCpy;
        SM.headIdxCpy = headIdx_cpy;
    }
}

static void ISRcallback()
{
    // Push new sample to the buffer
    sampBuf[ISRvars.headIdxVol] = HAL_getADCconv();

    // Increment buf indx
    ISRvars.headIdxVol = (ISRvars.headIdxVol >= SAMPLE_BUF_SIZE) ? 0 : (ISRvars.headIdxVol + 1);

    // If sampling has overrun sample processing, set collision flag
    ISRvars.b_collision |= (ISRvars.headIdxVol == SM.tailIdx);

    //todo: account for collisions!
}