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

// get/set POT1 aliases
#define POT1_TRIS                 TRISAbits.TRISA0
#define POT1_LAT                  LATAbits.LATA0
#define POT1_PORT                 PORTAbits.RA0
#define POT1_WPU                  WPUAbits.WPUA0
#define POT1_OD                   ODCONAbits.ODCA0
#define POT1_ANS                  ANSELAbits.ANSELA0
#define POT1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POT1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POT1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POT1_GetValue()           PORTAbits.RA0
#define POT1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POT1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POT1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define POT1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define POT1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define POT1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define POT1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define POT1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set BTNA aliases
#define BTNA_TRIS                 TRISAbits.TRISA3
#define BTNA_LAT                  LATAbits.LATA3
#define BTNA_PORT                 PORTAbits.RA3
#define BTNA_WPU                  WPUAbits.WPUA3
#define BTNA_OD                   ODCONAbits.ODCA3
#define BTNA_ANS                  ANSELAbits.ANSELA3
#define BTNA_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define BTNA_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define BTNA_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define BTNA_GetValue()           PORTAbits.RA3
#define BTNA_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define BTNA_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define BTNA_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define BTNA_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define BTNA_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define BTNA_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define BTNA_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define BTNA_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set BTNB aliases
#define BTNB_TRIS                 TRISAbits.TRISA4
#define BTNB_LAT                  LATAbits.LATA4
#define BTNB_PORT                 PORTAbits.RA4
#define BTNB_WPU                  WPUAbits.WPUA4
#define BTNB_OD                   ODCONAbits.ODCA4
#define BTNB_ANS                  ANSELAbits.ANSELA4
#define BTNB_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define BTNB_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define BTNB_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define BTNB_GetValue()           PORTAbits.RA4
#define BTNB_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define BTNB_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define BTNB_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define BTNB_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define BTNB_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define BTNB_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define BTNB_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define BTNB_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set G_DER aliases
#define G_DER_TRIS                 TRISBbits.TRISB2
#define G_DER_LAT                  LATBbits.LATB2
#define G_DER_PORT                 PORTBbits.RB2
#define G_DER_WPU                  WPUBbits.WPUB2
#define G_DER_OD                   ODCONBbits.ODCB2
#define G_DER_ANS                  ANSELBbits.ANSELB2
#define G_DER_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define G_DER_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define G_DER_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define G_DER_GetValue()           PORTBbits.RB2
#define G_DER_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define G_DER_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define G_DER_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define G_DER_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define G_DER_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define G_DER_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define G_DER_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define G_DER_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set G_IZQ aliases
#define G_IZQ_TRIS                 TRISCbits.TRISC2
#define G_IZQ_LAT                  LATCbits.LATC2
#define G_IZQ_PORT                 PORTCbits.RC2
#define G_IZQ_WPU                  WPUCbits.WPUC2
#define G_IZQ_OD                   ODCONCbits.ODCC2
#define G_IZQ_ANS                  ANSELCbits.ANSELC2
#define G_IZQ_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define G_IZQ_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define G_IZQ_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define G_IZQ_GetValue()           PORTCbits.RC2
#define G_IZQ_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define G_IZQ_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define G_IZQ_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define G_IZQ_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define G_IZQ_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define G_IZQ_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define G_IZQ_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define G_IZQ_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set G_STOP aliases
#define G_STOP_TRIS                 TRISCbits.TRISC3
#define G_STOP_LAT                  LATCbits.LATC3
#define G_STOP_PORT                 PORTCbits.RC3
#define G_STOP_WPU                  WPUCbits.WPUC3
#define G_STOP_OD                   ODCONCbits.ODCC3
#define G_STOP_ANS                  ANSELCbits.ANSELC3
#define G_STOP_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define G_STOP_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define G_STOP_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define G_STOP_GetValue()           PORTCbits.RC3
#define G_STOP_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define G_STOP_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define G_STOP_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define G_STOP_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define G_STOP_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define G_STOP_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define G_STOP_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define G_STOP_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set M_1 aliases
#define M_1_TRIS                 TRISDbits.TRISD1
#define M_1_LAT                  LATDbits.LATD1
#define M_1_PORT                 PORTDbits.RD1
#define M_1_WPU                  WPUDbits.WPUD1
#define M_1_OD                   ODCONDbits.ODCD1
#define M_1_ANS                  ANSELDbits.ANSELD1
#define M_1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define M_1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define M_1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define M_1_GetValue()           PORTDbits.RD1
#define M_1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define M_1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define M_1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define M_1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define M_1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define M_1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define M_1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define M_1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set M_2 aliases
#define M_2_TRIS                 TRISDbits.TRISD2
#define M_2_LAT                  LATDbits.LATD2
#define M_2_PORT                 PORTDbits.RD2
#define M_2_WPU                  WPUDbits.WPUD2
#define M_2_OD                   ODCONDbits.ODCD2
#define M_2_ANS                  ANSELDbits.ANSELD2
#define M_2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define M_2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define M_2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define M_2_GetValue()           PORTDbits.RD2
#define M_2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define M_2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define M_2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define M_2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define M_2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define M_2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define M_2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define M_2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set LEDC aliases
#define LEDC_TRIS                 TRISDbits.TRISD5
#define LEDC_LAT                  LATDbits.LATD5
#define LEDC_PORT                 PORTDbits.RD5
#define LEDC_WPU                  WPUDbits.WPUD5
#define LEDC_OD                   ODCONDbits.ODCD5
#define LEDC_ANS                  ANSELDbits.ANSELD5
#define LEDC_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define LEDC_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define LEDC_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define LEDC_GetValue()           PORTDbits.RD5
#define LEDC_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define LEDC_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define LEDC_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define LEDC_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define LEDC_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define LEDC_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define LEDC_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define LEDC_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set LEDB aliases
#define LEDB_TRIS                 TRISDbits.TRISD6
#define LEDB_LAT                  LATDbits.LATD6
#define LEDB_PORT                 PORTDbits.RD6
#define LEDB_WPU                  WPUDbits.WPUD6
#define LEDB_OD                   ODCONDbits.ODCD6
#define LEDB_ANS                  ANSELDbits.ANSELD6
#define LEDB_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define LEDB_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define LEDB_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define LEDB_GetValue()           PORTDbits.RD6
#define LEDB_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define LEDB_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define LEDB_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define LEDB_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define LEDB_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define LEDB_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define LEDB_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define LEDB_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set LEDA aliases
#define LEDA_TRIS                 TRISDbits.TRISD7
#define LEDA_LAT                  LATDbits.LATD7
#define LEDA_PORT                 PORTDbits.RD7
#define LEDA_WPU                  WPUDbits.WPUD7
#define LEDA_OD                   ODCONDbits.ODCD7
#define LEDA_ANS                  ANSELDbits.ANSELD7
#define LEDA_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define LEDA_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define LEDA_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define LEDA_GetValue()           PORTDbits.RD7
#define LEDA_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define LEDA_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define LEDA_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define LEDA_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define LEDA_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define LEDA_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define LEDA_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define LEDA_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set DATA_DHT aliases
#define DATA_DHT_TRIS                 TRISEbits.TRISE0
#define DATA_DHT_LAT                  LATEbits.LATE0
#define DATA_DHT_PORT                 PORTEbits.RE0
#define DATA_DHT_WPU                  WPUEbits.WPUE0
#define DATA_DHT_OD                   ODCONEbits.ODCE0
#define DATA_DHT_ANS                  ANSELEbits.ANSELE0
#define DATA_DHT_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define DATA_DHT_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define DATA_DHT_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define DATA_DHT_GetValue()           PORTEbits.RE0
#define DATA_DHT_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define DATA_DHT_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define DATA_DHT_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define DATA_DHT_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define DATA_DHT_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define DATA_DHT_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define DATA_DHT_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define DATA_DHT_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set BTNC aliases
#define BTNC_TRIS                 TRISEbits.TRISE2
#define BTNC_LAT                  LATEbits.LATE2
#define BTNC_PORT                 PORTEbits.RE2
#define BTNC_WPU                  WPUEbits.WPUE2
#define BTNC_OD                   ODCONEbits.ODCE2
#define BTNC_ANS                  ANSELEbits.ANSELE2
#define BTNC_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define BTNC_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define BTNC_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define BTNC_GetValue()           PORTEbits.RE2
#define BTNC_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define BTNC_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define BTNC_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define BTNC_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define BTNC_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define BTNC_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define BTNC_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define BTNC_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

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

// get/set TRIG aliases
#define TRIG_TRIS                 TRISFbits.TRISF6
#define TRIG_LAT                  LATFbits.LATF6
#define TRIG_PORT                 PORTFbits.RF6
#define TRIG_WPU                  WPUFbits.WPUF6
#define TRIG_OD                   ODCONFbits.ODCF6
#define TRIG_ANS                  ANSELFbits.ANSELF6
#define TRIG_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define TRIG_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define TRIG_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define TRIG_GetValue()           PORTFbits.RF6
#define TRIG_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define TRIG_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define TRIG_SetPullup()          do { WPUFbits.WPUF6 = 1; } while(0)
#define TRIG_ResetPullup()        do { WPUFbits.WPUF6 = 0; } while(0)
#define TRIG_SetPushPull()        do { ODCONFbits.ODCF6 = 0; } while(0)
#define TRIG_SetOpenDrain()       do { ODCONFbits.ODCF6 = 1; } while(0)
#define TRIG_SetAnalogMode()      do { ANSELFbits.ANSELF6 = 1; } while(0)
#define TRIG_SetDigitalMode()     do { ANSELFbits.ANSELF6 = 0; } while(0)

// get/set ECHO aliases
#define ECHO_TRIS                 TRISFbits.TRISF7
#define ECHO_LAT                  LATFbits.LATF7
#define ECHO_PORT                 PORTFbits.RF7
#define ECHO_WPU                  WPUFbits.WPUF7
#define ECHO_OD                   ODCONFbits.ODCF7
#define ECHO_ANS                  ANSELFbits.ANSELF7
#define ECHO_SetHigh()            do { LATFbits.LATF7 = 1; } while(0)
#define ECHO_SetLow()             do { LATFbits.LATF7 = 0; } while(0)
#define ECHO_Toggle()             do { LATFbits.LATF7 = ~LATFbits.LATF7; } while(0)
#define ECHO_GetValue()           PORTFbits.RF7
#define ECHO_SetDigitalInput()    do { TRISFbits.TRISF7 = 1; } while(0)
#define ECHO_SetDigitalOutput()   do { TRISFbits.TRISF7 = 0; } while(0)
#define ECHO_SetPullup()          do { WPUFbits.WPUF7 = 1; } while(0)
#define ECHO_ResetPullup()        do { WPUFbits.WPUF7 = 0; } while(0)
#define ECHO_SetPushPull()        do { ODCONFbits.ODCF7 = 0; } while(0)
#define ECHO_SetOpenDrain()       do { ODCONFbits.ODCF7 = 1; } while(0)
#define ECHO_SetAnalogMode()      do { ANSELFbits.ANSELF7 = 1; } while(0)
#define ECHO_SetDigitalMode()     do { ANSELFbits.ANSELF7 = 0; } while(0)

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