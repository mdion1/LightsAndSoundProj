#pragma once
#include <stdint.h>

typedef struct {
    int newSamples;
    const int16_t* buf;    //todo: int* should change to whatever width the samples are, OR make void* ?
}SigSampEvents_t;

void SigSamp_init();
SigSampEvents_t SigSamp_tasks();