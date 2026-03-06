/*
 * File:   LED.h
 * Author: T00904
 *
 * Created on January 8, 2026, 11:30 AM
 */

#ifndef LED_H
#define LED_H


#include "mcc_generated_files/mcc.h"
#include <xc.h>
extern void LED_main(void);

typedef union {
  struct {
    unsigned TURN : 1;
    unsigned DRL : 1;
    unsigned POS : 1;
    unsigned WHITE : 1;
    unsigned TEST : 1;
    unsigned WELCOME : 1;
    unsigned b6 : 1;
    unsigned b7 : 1;
  };
  uint8_t Byte;
} sflag;

// const uint8_t BIT_TURN= 0x01;
// const uint8_t BIT_DRL= 0x01<<1;
// const uint8_t BIT_POS= 0x01<<2;
// const uint8_t BIT_WHITE= 0x01<<3;
// const uint8_t BIT_TEST= 0x01<<4;
// const uint8_t BIT_WELCOME= 0x01<<5;
#define BIT_TURN 0x01;
#define BIT_DRL  (0x01<<1)
#define BIT_POS (0x01<<2)
#define BIT_WHITE (0x01<<3)
#define BIT_TEST (0x01<<4)
#define BIT_WELCOME (0x01<<5)

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
void tmr0_10ms_even(void);
void clear_no_call_warning_message(void);

void PWM_TURN_ON(void);
void DRL_on(void);
void POS_on(void);
void TURN_LIGHT_ON(void);
extern void all_led_off(void);

void all_yellow_led_turn_on(void);
void all_yellow_led_turn_off(void);
void all_white_led_turn_on(void);
void all_white_led_turn_off(void);

bool is_white(void);
bool is_turn_signals(void);
bool is_test(void);
bool is_DRL(void);
bool is_POS(void);
bool is_WELCOME(void);
void LED_main(void);

void PWM_DRL(void);
void PWM_POS(void);
void PWM_turn_signals(void);
void PWM_all_off(void);

void debounce_IO(void);
void turn_signals_state_update(void);
void check_welcome_signal(void);
void turn_on_turn_signals(void);
void delay_us(int8_t us);
void delay_ms(uint16_t ms);
void check_test_mode(void);
void check_POS_P2(void);

void white_fad_out(void);
void yellow_to_white(void);
void yellow_seg1_forward(void);
void yellow_seg2_forward(void);
void yellow_seg3_forward(void);
void yellow_seg4_forward(void);
void tellow_seg1_backward(void);
void yellow_seg2_backward(void);
void yellow_seg3_backward(void);
void yellow_seg4_backward(void);

void P2_on(void);
void P2_off(void);

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

#define ON 1
#define OFF 0
#define PWM1_DutyCycle_100PERCENT (799 + 1)
#define PWM1_DutyCycle_60PERCENT (479 + 1)
#define PWM1_DutyCycle_6PERCENT (47 + 1)
#define TURN_DELAY_MS 57
#define WELCOME_DELAY_MS 100
#define TEST_DELAY_MS 250
#define TURN_LIGHT_ON_600MS 400
#define WELCOME_LIGHT_TOTAL_MS 15000
#define II_CNT 7
#define PWM_MAX 10
#define TURN_LIGHT_OFF_600MS 600
#define TURN_TIMES_MAX 250
#define TURN_TIMER_MAX 3000
#define WELCOME_TIMES 2

// const uint8_t ON = 1;
// const uint8_t OFF = 0;
// const uint16_t PWM1_DutyCycle_100PERCENT = 799 + 1;
// const uint16_t PWM1_DutyCycle_60PERCENT = 479 + 1;
// const uint16_t PWM1_DutyCycle_6PERCENT = 47 + 1;
// const uint8_t TURN_DELAY_MS = 57;
// const uint8_t WELCOME_DELAY_MS = 100;
// const uint8_t TEST_DELAY_MS = 250;
// const uint16_t TURN_LIGHT_ON_600MS = 400;
// const uint16_t WELCOME_LIGHT_TOTAL_MS = 15000;
// const uint8_t II_CNT = 7;
// const uint8_t PWM_MAX = 10;

// const uint16_t TURN_LIGHT_OFF_600MS = 600;
// const uint8_t TURN_TIMES_MAX = 250;
// const uint16_t TURN_TIMER_MAX = 3000;
// const uint8_t WELCOME_TIMES = 2;



#endif /* LED_H */
