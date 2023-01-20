#pragma once
#include <stdint.h>
#include <stdbool.h>

void SigSamp_init();
void SigSamp_start();
void SigSamp_stop();
void SigSamp_tasks();
uint16_t SigSamp_getNumSamples();
const int16_t* SigSamp_getSampBuf();
bool SigSamp_isActive();