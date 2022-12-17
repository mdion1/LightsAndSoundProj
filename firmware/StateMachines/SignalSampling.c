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
    int headIdx;
    int tailIdx;
}SM;

// State machine owned by the ISR
static volatile struct {
    int x;
}ISRvars;

// Sample buffer
static int16_t sampBuf[SAMPLE_BUF_SIZE];
static int bufIdx = 0;

/* Private function declarations */
static void resetBuf();
static void samplingTasks();

/* Public function definitions */

void SigSamp_init()
{
    SM.state = IDLE;
    resetBuf();
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
            events.newSamples = SM.headIdx - SM.tailIdx;
            events.buf = &sampBuf[SM.tailIdx];
        break;
    }

    return events;
}

/* Private function definitions */
static void resetBuf()
{
    SM.headIdx = SM.tailIdx = 0;

    //critical section ("di"/"ei"), reset volatile ISR vars
}

static void samplingTasks()
{
    // check HAL for new samples
    // if DMA is available, implement ping-pong buffer
    // if interrupt-driven, copy volatile variables that track new sample counts;


    SM.tailIdx = SM.headIdx;
    SM.headIdx = /* get # of new samples */ 0;
}

/* ISR */
void ISR()
{
    //todo
    ISRvars.x = 0;
}