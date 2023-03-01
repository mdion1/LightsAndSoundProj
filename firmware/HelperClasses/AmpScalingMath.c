
#define GAMMALOOKUP_LEN 64
#define MASK_LSB_START 0x7fff
#define GAMMA_LEFTSHIFT 5

static const uint8_t gammaLookup;



void Gamma(uint16_t val)
{
    uint16_t maskMSB = 0x8000;
    uint16_t maskLSB = MASK_LSB_START;
    
    int msb = 15;
    int lsb = 0;
    while (msb)
    {
        if(val & maskMSB) {
            lsb = gammaLookup[val & maskLSB];
            break;
        }
        msb--;
    }
    return (msb << GAMMA_LEFTSHIFT) + lsb;
}

static const uint8_t gammaLookup[GAMMALOOKUP_LEN] = {
    
};
