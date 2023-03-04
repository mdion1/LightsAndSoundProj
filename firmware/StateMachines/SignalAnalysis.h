#pragma once
#include <stdint.h>
#include <stdbool.h>

void SigAnalysis_init();
void SigAnalysis_reset();
void SigAnalysis_tasks();
void SigAnalysis_getSigStr(int32_t* pSinOut, int32_t* pCosOut, uint8_t* numCycles); // does not check for null ptr input arguments