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
        Device            :  PIC16F1936
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

// get/set YellowLed01 aliases
#define YellowLed01_TRIS                 TRISAbits.TRISA0
#define YellowLed01_LAT                  LATAbits.LATA0
#define YellowLed01_PORT                 PORTAbits.RA0
#define YellowLed01_ANS                  ANSELAbits.ANSA0
#define YellowLed01_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define YellowLed01_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define YellowLed01_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define YellowLed01_GetValue()           PORTAbits.RA0
#define YellowLed01_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define YellowLed01_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define YellowLed01_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define YellowLed01_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set YellowLed02 aliases
#define YellowLed02_TRIS                 TRISAbits.TRISA1
#define YellowLed02_LAT                  LATAbits.LATA1
#define YellowLed02_PORT                 PORTAbits.RA1
#define YellowLed02_ANS                  ANSELAbits.ANSA1
#define YellowLed02_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define YellowLed02_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define YellowLed02_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define YellowLed02_GetValue()           PORTAbits.RA1
#define YellowLed02_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define YellowLed02_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define YellowLed02_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define YellowLed02_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set YellowLed03 aliases
#define YellowLed03_TRIS                 TRISAbits.TRISA2
#define YellowLed03_LAT                  LATAbits.LATA2
#define YellowLed03_PORT                 PORTAbits.RA2
#define YellowLed03_ANS                  ANSELAbits.ANSA2
#define YellowLed03_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define YellowLed03_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define YellowLed03_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define YellowLed03_GetValue()           PORTAbits.RA2
#define YellowLed03_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define YellowLed03_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define YellowLed03_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define YellowLed03_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set YellowLed04 aliases
#define YellowLed04_TRIS                 TRISAbits.TRISA3
#define YellowLed04_LAT                  LATAbits.LATA3
#define YellowLed04_PORT                 PORTAbits.RA3
#define YellowLed04_ANS                  ANSELAbits.ANSA3
#define YellowLed04_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define YellowLed04_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define YellowLed04_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define YellowLed04_GetValue()           PORTAbits.RA3
#define YellowLed04_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define YellowLed04_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define YellowLed04_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define YellowLed04_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set YellowLed05 aliases
#define YellowLed05_TRIS                 TRISAbits.TRISA4
#define YellowLed05_LAT                  LATAbits.LATA4
#define YellowLed05_PORT                 PORTAbits.RA4
#define YellowLed05_ANS                  ANSELAbits.ANSA4
#define YellowLed05_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define YellowLed05_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define YellowLed05_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define YellowLed05_GetValue()           PORTAbits.RA4
#define YellowLed05_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define YellowLed05_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define YellowLed05_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define YellowLed05_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set YellowLed06 aliases
#define YellowLed06_TRIS                 TRISAbits.TRISA5
#define YellowLed06_LAT                  LATAbits.LATA5
#define YellowLed06_PORT                 PORTAbits.RA5
#define YellowLed06_ANS                  ANSELAbits.ANSA5
#define YellowLed06_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define YellowLed06_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define YellowLed06_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define YellowLed06_GetValue()           PORTAbits.RA5
#define YellowLed06_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define YellowLed06_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define YellowLed06_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define YellowLed06_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set YellowLed08 aliases
#define YellowLed08_TRIS                 TRISAbits.TRISA6
#define YellowLed08_LAT                  LATAbits.LATA6
#define YellowLed08_PORT                 PORTAbits.RA6
#define YellowLed08_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define YellowLed08_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define YellowLed08_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define YellowLed08_GetValue()           PORTAbits.RA6
#define YellowLed08_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define YellowLed08_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set YellowLed07 aliases
#define YellowLed07_TRIS                 TRISAbits.TRISA7
#define YellowLed07_LAT                  LATAbits.LATA7
#define YellowLed07_PORT                 PORTAbits.RA7
#define YellowLed07_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define YellowLed07_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define YellowLed07_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define YellowLed07_GetValue()           PORTAbits.RA7
#define YellowLed07_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define YellowLed07_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set iTestPin aliases
#define iTestPin_TRIS                 TRISBbits.TRISB0
#define iTestPin_LAT                  LATBbits.LATB0
#define iTestPin_PORT                 PORTBbits.RB0
#define iTestPin_WPU                  WPUBbits.WPUB0
#define iTestPin_ANS                  ANSELBbits.ANSB0
#define iTestPin_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define iTestPin_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define iTestPin_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define iTestPin_GetValue()           PORTBbits.RB0
#define iTestPin_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define iTestPin_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define iTestPin_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define iTestPin_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define iTestPin_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define iTestPin_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set iTurnSignal aliases
#define iTurnSignal_TRIS                 TRISBbits.TRISB1
#define iTurnSignal_LAT                  LATBbits.LATB1
#define iTurnSignal_PORT                 PORTBbits.RB1
#define iTurnSignal_WPU                  WPUBbits.WPUB1
#define iTurnSignal_ANS                  ANSELBbits.ANSB1
#define iTurnSignal_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define iTurnSignal_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define iTurnSignal_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define iTurnSignal_GetValue()           PORTBbits.RB1
#define iTurnSignal_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define iTurnSignal_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define iTurnSignal_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define iTurnSignal_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define iTurnSignal_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define iTurnSignal_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set iWelcome aliases
#define iWelcome_TRIS                 TRISBbits.TRISB2
#define iWelcome_LAT                  LATBbits.LATB2
#define iWelcome_PORT                 PORTBbits.RB2
#define iWelcome_WPU                  WPUBbits.WPUB2
#define iWelcome_ANS                  ANSELBbits.ANSB2
#define iWelcome_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define iWelcome_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define iWelcome_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define iWelcome_GetValue()           PORTBbits.RB2
#define iWelcome_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define iWelcome_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define iWelcome_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define iWelcome_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define iWelcome_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define iWelcome_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set iP2 aliases
#define iP2_TRIS                 TRISBbits.TRISB3
#define iP2_LAT                  LATBbits.LATB3
#define iP2_PORT                 PORTBbits.RB3
#define iP2_WPU                  WPUBbits.WPUB3
#define iP2_ANS                  ANSELBbits.ANSB3
#define iP2_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define iP2_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define iP2_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define iP2_GetValue()           PORTBbits.RB3
#define iP2_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define iP2_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define iP2_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define iP2_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define iP2_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define iP2_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set iDRL aliases
#define iDRL_TRIS                 TRISBbits.TRISB4
#define iDRL_LAT                  LATBbits.LATB4
#define iDRL_PORT                 PORTBbits.RB4
#define iDRL_WPU                  WPUBbits.WPUB4
#define iDRL_ANS                  ANSELBbits.ANSB4
#define iDRL_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define iDRL_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define iDRL_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define iDRL_GetValue()           PORTBbits.RB4
#define iDRL_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define iDRL_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define iDRL_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define iDRL_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define iDRL_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define iDRL_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set iPOS aliases
#define iPOS_TRIS                 TRISBbits.TRISB5
#define iPOS_LAT                  LATBbits.LATB5
#define iPOS_PORT                 PORTBbits.RB5
#define iPOS_WPU                  WPUBbits.WPUB5
#define iPOS_ANS                  ANSELBbits.ANSB5
#define iPOS_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define iPOS_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define iPOS_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define iPOS_GetValue()           PORTBbits.RB5
#define iPOS_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define iPOS_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define iPOS_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define iPOS_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define iPOS_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define iPOS_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set YellowLed09 aliases
#define YellowLed09_TRIS                 TRISCbits.TRISC0
#define YellowLed09_LAT                  LATCbits.LATC0
#define YellowLed09_PORT                 PORTCbits.RC0
#define YellowLed09_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define YellowLed09_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define YellowLed09_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define YellowLed09_GetValue()           PORTCbits.RC0
#define YellowLed09_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define YellowLed09_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set YellowLed10 aliases
#define YellowLed10_TRIS                 TRISCbits.TRISC1
#define YellowLed10_LAT                  LATCbits.LATC1
#define YellowLed10_PORT                 PORTCbits.RC1
#define YellowLed10_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define YellowLed10_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define YellowLed10_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define YellowLed10_GetValue()           PORTCbits.RC1
#define YellowLed10_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define YellowLed10_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

// get/set WhiteLed01 aliases
#define WhiteLed01_TRIS                 TRISCbits.TRISC3
#define WhiteLed01_LAT                  LATCbits.LATC3
#define WhiteLed01_PORT                 PORTCbits.RC3
#define WhiteLed01_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define WhiteLed01_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define WhiteLed01_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define WhiteLed01_GetValue()           PORTCbits.RC3
#define WhiteLed01_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define WhiteLed01_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set SideLight aliases
#define SideLight_TRIS                 TRISCbits.TRISC4
#define SideLight_LAT                  LATCbits.LATC4
#define SideLight_PORT                 PORTCbits.RC4
#define SideLight_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SideLight_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SideLight_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SideLight_GetValue()           PORTCbits.RC4
#define SideLight_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SideLight_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set iYelowWhiteSelect aliases
#define iYelowWhiteSelect_TRIS                 TRISCbits.TRISC5
#define iYelowWhiteSelect_LAT                  LATCbits.LATC5
#define iYelowWhiteSelect_PORT                 PORTCbits.RC5
#define iYelowWhiteSelect_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define iYelowWhiteSelect_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define iYelowWhiteSelect_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define iYelowWhiteSelect_GetValue()           PORTCbits.RC5
#define iYelowWhiteSelect_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define iYelowWhiteSelect_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

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