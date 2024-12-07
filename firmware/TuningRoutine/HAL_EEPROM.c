#include "HAL_EEPROM.h"
#include <xc.h>

// EEPROM memory lies from 0x380000 to 0x3801ff (512 bytes).
#define EEPROM_BASE 0x380000
#define EEPROM_SIZE 512

typedef enum {
    NVMCMD_READ = 0,
    NVMCMD_WRITE = 3,
} NVMCMD_t;

uint8_t EEPROM_read(uint16_t addrOffset) {
    /* From the datasheet (Section 10.4.1):
     * To read a DFM (EEPROM) location, the user must write the address to the NVMADR register, set the NVMCMD bits for a
     * single read operation (NVMCMD = ‘b000), and then set the GO control bit. The data is available on the very next
     * instruction cycle. Therefore, the NVMDATL register can be read by the next instruction.
     */
    if (addrOffset >= EEPROM_SIZE) {
        return 0;
    }

    NVMADR = addrOffset + EEPROM_BASE;
    NVMCON1bits.CMD = NVMCMD_READ;
    NVMCON0bits.GO = 1;
    while (NVMCON0bits.GO);
    return NVMDATL;
}

bool EEPROM_write(uint16_t addrOffset, uint8_t val) {
    /* From the datasheet (Section 10.4.2):
     * To write a DFM (EEPROM) location, the address must first be written to the NVMADR register, the data written to the NVMDATL
     * register, and the Write operation command set in the NVMCMD bits. The sequence shown in Unlock Sequence must
     * be followed to initiate the write cycle.
     */
    if (addrOffset >= EEPROM_SIZE) {
        return false;
    }
    
    NVMADR = addrOffset + EEPROM_BASE;
    NVMDATL = val;
    NVMCON1bits.CMD = NVMCMD_WRITE;
    //todo disable interrupts
    NVMLOCK = 0x55;
    NVMLOCK = 0xAA;
    NVMCON0bits.GO = 1;
    while (NVMCON0bits.GO);
    if (NVMCON1bits.WRERR) {
        return false;
    }

    // Verify (side-effect: resets CMD to "read")
    return EEPROM_read(addrOffset) == val;
}
