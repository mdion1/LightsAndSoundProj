#pragma once
#include <stdint.h>
#include <stdbool.h>

void SigSamp_init(void);
void SigSamp_start(void);
void SigSamp_stop(void);
void SigSamp_tasks(void);
uint8_t SigSamp_getTimebase(void);       // This value is updated once per task loop
void SigSamp_getSigStr(int32_t* pSinOut, int32_t* pCosOut, uint8_t* numCycles); // does not check for null ptr input arguments