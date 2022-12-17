#include "SignalAnalysis.h"
#include "SamplingParams.h"
#include "../HelperClasses/WindowAvg.h"

/* Private variable declarations */
static struct
{
    int sin[NUM_BUFS];
    int cos[NUM_BUFS];
}rollingAvgBufs;

WndAvg_t wndAvg_sin;
WndAvg_t wndAvg_cos;

//State machine
static struct
{
    //partially-filled buffer
    int sumSin;
    int sumCos;
    int sumCnt;

    //newest signal strength data
    int sigStrn;
    bool b_validSigStrn;
}SM;


/* Private function declarations */
static void onSumComplete();

/* Public function definitions */

void SigAnalysis_init()
{
    //todo: init SM struct

    WndAvg_init(&wndAvg_sin, rollingAvgBufs.sin);
    WndAvg_init(&wndAvg_cos, rollingAvgBufs.cos);
}

SigAnl_t SigAnalysis_tasks(int newSampCnt, void* buf)
{
    SM.b_validSigStrn = false;  //Flag is valid only for one task loop

    for (int i = 0; i < newSampCnt; i++)
    {
        SM.sumSin += sinTable[SM.sumCnt] * ((int16_t*)buf)[i];      //todo: implement hardware-accelerated mult/add; figure out sample width
        SM.sumCos += cosTable[SM.sumCnt] * ((int16_t*)buf)[i];      //todo: implement hardware-accelerated mult/add; figure out sample width
        SM.sumCnt++;

        if (SM.sumCnt >= SAMPLE_BUF_SIZE)
        {
            onSumComplete();
        }
    }

    return (SigAnl_t) {
        .b_newData = SM.b_validSigStrn,
    };
}

/* Private function definitions */

static void onSumComplete()
{
    //push sums into WindowAvg buffers
    int avgIm = WndAvg_pushVal(&wndAvg_sin, SM.sumSin);
    int avgRe = WndAvg_pushVal(&wndAvg_cos, SM.sumCos);

    // calculate abs(Re,Im)
    SM.sigStrn = avgIm * avgIm + avgRe * avgRe;
    SM.b_validSigStrn = true;
}