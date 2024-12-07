
#pragma once
#include <stdint.h>
#include <stdbool.h>

uint8_t EEPROM_read(uint16_t addrOffset);
bool EEPROM_write(uint16_t addrOffset, uint8_t val);