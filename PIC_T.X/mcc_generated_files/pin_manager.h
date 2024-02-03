/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F57Q43
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED1 aliases
#define LED1_TRIS                 TRISBbits.TRISB0
#define LED1_LAT                  LATBbits.LATB0
#define LED1_PORT                 PORTBbits.RB0
#define LED1_WPU                  WPUBbits.WPUB0
#define LED1_OD                   ODCONBbits.ODCB0
#define LED1_ANS                  ANSELBbits.ANSELB0
#define LED1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define LED1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define LED1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define LED1_GetValue()           PORTBbits.RB0
#define LED1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define LED1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISBbits.TRISB1
#define LED2_LAT                  LATBbits.LATB1
#define LED2_PORT                 PORTBbits.RB1
#define LED2_WPU                  WPUBbits.WPUB1
#define LED2_OD                   ODCONBbits.ODCB1
#define LED2_ANS                  ANSELBbits.ANSELB1
#define LED2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define LED2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define LED2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define LED2_GetValue()           PORTBbits.RB1
#define LED2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define LED2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS                 TRISBbits.TRISB2
#define LED3_LAT                  LATBbits.LATB2
#define LED3_PORT                 PORTBbits.RB2
#define LED3_WPU                  WPUBbits.WPUB2
#define LED3_OD                   ODCONBbits.ODCB2
#define LED3_ANS                  ANSELBbits.ANSELB2
#define LED3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LED3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define LED3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define LED3_GetValue()           PORTBbits.RB2
#define LED3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define LED3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define LED3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define LED3_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define LED3_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define LED3_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define LED3_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RF0 procedures
#define RF0_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define RF0_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define RF0_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define RF0_GetValue()              PORTFbits.RF0
#define RF0_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define RF0_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define RF0_SetPullup()             do { WPUFbits.WPUF0 = 1; } while(0)
#define RF0_ResetPullup()           do { WPUFbits.WPUF0 = 0; } while(0)
#define RF0_SetAnalogMode()         do { ANSELFbits.ANSELF0 = 1; } while(0)
#define RF0_SetDigitalMode()        do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 procedures
#define RF1_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define RF1_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define RF1_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define RF1_GetValue()              PORTFbits.RF1
#define RF1_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define RF1_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define RF1_SetPullup()             do { WPUFbits.WPUF1 = 1; } while(0)
#define RF1_ResetPullup()           do { WPUFbits.WPUF1 = 0; } while(0)
#define RF1_SetAnalogMode()         do { ANSELFbits.ANSELF1 = 1; } while(0)
#define RF1_SetDigitalMode()        do { ANSELFbits.ANSELF1 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/