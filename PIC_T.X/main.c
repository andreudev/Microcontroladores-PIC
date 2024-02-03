

#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/uart1.h"
#include "funtions_frame.h"



/*
                         Main application
 */

extern char frame[RX_BUFFER_SIZE];
extern int index;

void main(void)
{
    SYSTEM_Initialize();
    char string[MAX_SIZE];
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    while (1)
    {
        if (LED1_GetValue()==0) {
            printf("led1#");
        }
        if (LED2_GetValue()==0) {
            printf("led2#");
        }
        if (LED3_GetValue()==0) {
            printf("led3#");
        }

    }
}
