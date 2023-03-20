#pragma once
#include <stdint.h>
#include <stdbool.h>

void Sleep_init(void);
void Sleep_tasks(void);
void SleepTest(void);       // Powers down peripherals and puts microcontroller to sleep for longest defined sleep timer duration