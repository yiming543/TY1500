/*
 * File:   LED.h
 * Author: T00904
 *
 * Created on January 8, 2026, 11:30 AM
 */

#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
#include <xc.h>

typedef union {
  struct {
    _Bool TURN : 1;
    _Bool DRL : 1;
    _Bool POS : 1;
    _Bool WHITE : 1;
    _Bool TEST : 1;
    _Bool b5 : 1;
    _Bool b6 : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} sflag;

const uint8_t BIT_TURN= 0x01;
const uint8_t BIT_DRL= 0x01<<1;
const uint8_t BIT_POS= 0x01<<2;
const uint8_t BIT_WHITE= 0x01<<3;
const uint8_t BIT_TEST= 0x01<<4;

typedef enum {
  TURN_STEP_0 = 0,
  TURN_STEP_1,
  TURN_STEP_2,
  TURN_STEP_3,
  TURN_STEP_4,
} eTURN_STEP;

typedef enum {
  WELCOME_STEP_0 = 0,
  WELCOME_STEP_1,
  WELCOME_STEP_2,
  WELCOME_STEP_3,
  WELCOME_STEP_4,
  WELCOME_STEP_5,
  WELCOME_STEP_6,
  WELCOME_STEP_7,
  WELCOME_STEP_8,
  WELCOME_STEP_9,
  WELCOME_STEP_10,
  WELCOME_STEP_11,
  WELCOME_STEP_12,
  WELCOME_STEP_13,
  WELCOME_STEP_14,
} eWELCOME_STEP;

//extern
extern sflag ORB;
extern const uint16_t PWM[];

//ISR
void TMR0_10MS_Even(void);
void Clear_No_Call_Warning(void);

void PWM_TURN_ON(void);
void DRL_ON(void);
void POS_ON(void);
void TURN_LIGHT_ON(void);
void ALL_LED_OFF(void);

void YLED_ALL_ON(void);
void YLED_ALL_OFF(void);
void WLED_ALL_ON(void);
void WLED_ALL_OFF(void);

bool IsWhite(void);
bool IsTurnSignal(void);
bool IsTest(void);
bool IsDRL(void);
bool IsPOS(void);
void LED_main(void);

void PWM_DRL(void);
void PWM_POS(void);
void PWM_TURN_LIGHT(void);
void PWM_ALL_OFF(void);

void Debounce_IO(void);
void CheckTurnSignals(void);
void TurnOnTurnSignals(void);
void delay_us(int8_t us);
void delay_ms(uint16_t ms);
void CheckTestMode(void);
void CheckPOS_P2(void);

void White_fad_out(void);
void YellowToWhite(void);
void Yellow_SEG1_forward(void);
void Yellow_SEG2_forward(void);
void Yellow_SEG3_forward(void);
void Yellow_SEG4_forward(void);
void Yellow_SEG1_backward(void);
void Yellow_SEG2_backward(void);
void Yellow_SEG3_backward(void);
void Yellow_SEG4_backward(void);

void P2_ON(void);
void P2_OFF(void);

#define YLED01 LATAbits.LATA0
#define YLED02 LATAbits.LATA1
#define YLED03 LATAbits.LATA2
#define YLED04 LATAbits.LATA3
#define YLED05 LATAbits.LATA4
#define YLED06 LATAbits.LATA5
#define YLED07 LATAbits.LATA7
#define YLED08 LATAbits.LATA6
#define YLED09 LATCbits.LATC0
#define YLED10 LATCbits.LATC1
#define LED_en LATCbits.LATC2
#define WLED01 LATCbits.LATC3

const uint8_t ON = 1;
const uint8_t OFF = 0;
const uint16_t PWM1_DutyCycle_100PERCENT = 799 + 1;
const uint16_t PWM1_DutyCycle_60PERCENT = 479 + 1;
const uint16_t PWM1_DutyCycle_6PERCENT = 47 + 1;
const uint8_t TURN_DELAY_MS = 57; // 75
const uint8_t WELCOME_DELAY_MS = 100;
const uint8_t TEST_DELAY_MS = 250;
const uint16_t TURN_LIGHT_ON_600MS = 400;
const uint16_t WELCOME_LIGHT_TOTAL_MS = 15000;
const uint16_t TURN_LIGHT_OFF_600MS = 1000;
const uint8_t II_CNT = 7;
const uint8_t PWM_MAX = 10;

#ifdef __cplusplus
}
#endif

#endif /* LED_H */
