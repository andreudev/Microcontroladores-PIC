

#include "mcc_generated_files/mcc.h"


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        I2C_WriteNBytes(0b01000000,0x0F,1);
        __delay_ms(500);
        I2C_WriteNBytes(0b01000000,0xF0,1);
        __delay_ms(500);
    }
}