#pragma once
#include <stdint.h>

void OscTune_incrFreq(void);
void OscTune_decrFreq(void);
int8_t OscTune_getTun(void);
void OscTune_setTun(int8_t val);