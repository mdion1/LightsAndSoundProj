#pragma once
#include <stdint.h>
#include <stdbool.h>

void SigSamp_init();
void SigSamp_start();
void SigSamp_stop();
void SigSamp_tasks();
uint8_t SigSamp_getNumSamples();       // This value is updated once per task loop
uint16_t SigSamp_getTimebase();
const int16_t* SigSamp_getSampBuf();