#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct SignalAnalysis
{
    bool b_newData;
}SigAnl_t;


void SigAnalysis_init();
SigAnl_t SigAnalysis_tasks();