/*
 * File:   LED.c
 * Author: T00904
 * MCU:PIC16F1936
 * 功能:控制DRL/POS/方向燈/迎賓燈
 * Created on January 8, 2026, 11:29 AM
 */

#include "LED.h"
#include <stdint.h>
#include <xc.h>

// RAM
uint16_t turn_1ms_cnt = 0;
uint32_t welcome_1ms_cnt = 0;
uint16_t tDelay_ms = TURN_DELAY_MS;
sflag ORB = {0};
bool f1ms = 0;
// bool f5S = 0;
eWELCOME_STEP eWelcome_step = WELCOME_STEP_0;
bool fWelcome_light = 0;
bool fWelcome_light_disable = 0;

bool fturn_state = OFF;
bool fturn_light_disable = 0;
uint16_t turn_off_cnt = 0;
eTURN_STEP eTurn_step = TURN_STEP_0;
uint8_t turn_fall_edge_cnt = 0;
bool fturn_off_600ms = 0;

// 消除未呼叫警告訊息 假裝有使用這些函數
void clear_no_call_warning_message(void) {
  uint8_t i = 0;
  if (i == 1) {
    TMR0_ReadTimer();
    TMR0_WriteTimer(0);
    TMR0_ReadTimer();
    TMR0_WriteTimer(0);
    TMR0_Reload();
  } else if (i == 2) {
    TMR2_StartTimer();
    TMR2_StopTimer();
    TMR2_ReadTimer();
    TMR2_WriteTimer(0);
    TMR2_LoadPeriodRegister(0);
    TMR2_HasOverflowOccured();
  } else if (i == 3) {
    PWM_all_off();
    PIN_MANAGER_IOC();
  } else if (i == 4) {
  } else if (i == 5) {
  } else if (i == 6) {
  }
}

// 消除彈跳
void debounce_IO(void) {
  static sflag TRB = {0};
  uint8_t temp = 0;
  if (is_turn_signals()) {
    temp |= BIT_TURN;
  }
  if (is_DRL()) {
    temp |= BIT_DRL;
  }
  if (is_POS()) {
    temp |= BIT_POS;
  }
  if (is_white()) {
    temp |= BIT_WHITE;
  }
  if (is_test()) {
    temp |= BIT_TEST;
  }
  if (is_WELCOME()) {
    temp |= BIT_WELCOME;
  }
  if (temp ^ TRB.Byte) {
    TRB.Byte = temp;
  } else {
    ORB.Byte = temp;
  }
}

// 檢查方向燈信號
void turn_signals_state_update(void) {
  if (ORB.TURN) {
    fturn_state = ON;
    fturn_off_600ms = 0;
    fturn_light_disable = 0;
  } else {
    // 下降緣
    if (fturn_state) {
      all_led_off();
      turn_off_cnt = 0;
      if (turn_fall_edge_cnt < TURN_TIMES_MAX) {
        turn_fall_edge_cnt++;
      }
    } else {
      if (turn_off_cnt < TURN_LIGHT_OFF_600MS) {
        turn_off_cnt++;
      } else {
        fturn_off_600ms = 1;
      }
    }
    fturn_state = OFF;
    fturn_light_disable = 1;
  }
}

void check_welcome_signal(void) {
  // turn signal off 600ms
  if (fturn_off_600ms) {
    if (turn_fall_edge_cnt == WELCOME_TIMES ) {
      fWelcome_light = 1;
    }
    turn_fall_edge_cnt = 0;
  }
}

// 所有黃光ON
void all_yellow_led_turn_on(void) {
  LATA |= 0xff;
  LATC |= 0x03;
}

// 所有黃光OFF
void all_yellow_led_turn_off(void) {
  LATA &= 0x00;
  LATC &= 0xFC;
}

// 白光ON/OFF
void all_white_led_turn_on(void) { WLED01 = ON; }
void all_white_led_turn_off(void) { WLED01 = OFF; }

// P2 ON/OFF
void P2_on(void) { SideLight_SetHigh(); }
void P2_off(void) { SideLight_SetLow(); }

// PWM工作週期設定
void PWM_DRL(void) { EPWM1_LoadDutyValue(PWM1_DutyCycle_60PERCENT); }
void PWM_POS(void) { EPWM1_LoadDutyValue(PWM1_DutyCycle_6PERCENT); }
void PWM_turn_signals(void) { EPWM1_LoadDutyValue(PWM1_DutyCycle_100PERCENT); }
void PWM_all_off(void) { EPWM1_LoadDutyValue(0); }

// 畫行燈
void DRL_on(void) {
  if (ORB.WHITE) {
    all_yellow_led_turn_off();
  } else {
    all_white_led_turn_off();
  }
  PWM_DRL();
  if (ORB.WHITE) {
    all_white_led_turn_on();
  } else {
    all_yellow_led_turn_on();
  }
}

// 位置燈
void POS_on(void) {
  if (ORB.WHITE) {
    all_yellow_led_turn_off();
  } else {
    all_white_led_turn_off();
  }
  PWM_POS();
  if (ORB.WHITE) {
    all_white_led_turn_on();
  } else {
    all_yellow_led_turn_on();
  }
}

// 所有LED OFF
void all_led_off(void) {
  all_yellow_led_turn_off();
  all_white_led_turn_off();
  PWM_turn_signals();
}

// 檢查輸入
bool is_white(void) { return iYelowWhiteSelect_PORT; }
bool is_turn_signals(void) { return iTurnSignal_PORT; }
bool is_test(void) { return iTestPin_PORT; }
bool is_DRL(void) { return iDRL_PORT; }
bool is_POS(void) { return iPOS_PORT; }
bool is_WELCOME(void) { return iWelcome_PORT; }

// TMR0中斷副程式10ms event
void tmr0_10ms_even(void) {
  f1ms = 1;
  welcome_1ms_cnt++;
  turn_1ms_cnt++;
}

// user 延遲us副程式
void delay_us(int8_t us) {
  while (us--)
    __delay_us(148);
}

// user 延遲ms副程式
void delay_ms(uint16_t ms) {
  while (ms--) {
    if (iTurnSignal_PORT) {
      break;
    }
    __delay_us(990);
  }
}

// 黃光轉白光
void yellow_to_white(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx >= 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < 50; ii++) {
      all_yellow_led_turn_on();
      all_white_led_turn_off();
      delay_us(pwm_idx);
      all_yellow_led_turn_off();
      all_white_led_turn_on();
      delay_us(PWM_MAX - pwm_idx);
    }
  }
  all_white_led_turn_on();
}

// 白光漸滅
void white_fad_out(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx >= 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < 25; ii++) {
      all_white_led_turn_on();
      delay_us(pwm_idx);
      all_white_led_turn_off();
      delay_us(PWM_MAX - pwm_idx);
    }
  }
}

// 黃光 第一段 前進
void yellow_seg1_forward(void) {
  for (int8_t pwm_idx = 1; pwm_idx <= PWM_MAX; pwm_idx++) {
    if (iTurnSignal_PORT) {
      break;
    }
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED10 = 1;
      YLED09 = 1;
      delay_us(pwm_idx);
      YLED10 = 0;
      YLED09 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
  YLED10 = 1;
  YLED09 = 1;
}

// 黃光 第二段 前進
void yellow_seg2_forward(void) {
  for (int8_t pwm_idx = 1; pwm_idx <= PWM_MAX; pwm_idx++) {
    if (iTurnSignal_PORT) {
      break;
    }
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED08 = 1;
      YLED05 = 1;
      delay_us(pwm_idx);
      YLED08 = 0;
      YLED05 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
  YLED08 = 1;
  YLED05 = 1;
}

// 黃光 第三段 前進
void yellow_seg3_forward(void) {
  for (int8_t pwm_idx = 1; pwm_idx <= PWM_MAX; pwm_idx++) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED07 = 1;
      YLED03 = 1;
      YLED04 = 1;
      delay_us(pwm_idx);
      YLED07 = 0;
      YLED03 = 0;
      YLED04 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
  YLED07 = 1;
  YLED03 = 1;
  YLED04 = 1;
}

// 黃光 第四段 前進
void yellow_seg4_forward(void) {
  for (int8_t pwm_idx = 1; pwm_idx <= PWM_MAX; pwm_idx++) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED06 = 1;
      YLED01 = 1;
      YLED02 = 1;
      delay_us(pwm_idx);
      YLED06 = 0;
      YLED01 = 0;
      YLED02 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
  YLED06 = 1;
  YLED01 = 1;
  YLED02 = 1;
}

// 黃光 第一段 退後
void tellow_seg1_backward(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx > 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED06 = 1;
      YLED01 = 1;
      YLED02 = 1;
      delay_us(pwm_idx);
      YLED06 = 0;
      YLED01 = 0;
      YLED02 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
}

// 黃光 第二段 退後
void yellow_seg2_backward(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx > 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED07 = 1;
      YLED03 = 1;
      YLED04 = 1;
      delay_us(pwm_idx);
      YLED07 = 0;
      YLED03 = 0;
      YLED04 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
}

// 黃光 第三段 退後
void yellow_seg3_backward(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx > 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED08 = 1;
      YLED05 = 1;
      delay_us(pwm_idx);
      YLED08 = 0;
      YLED05 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
}

// 黃光 第四段 退後
void yellow_seg4_backward(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx > 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < II_CNT; ii++) {
      YLED09 = 1;
      YLED10 = 1;
      delay_us(pwm_idx);
      YLED09 = 0;
      YLED10 = 0;
      delay_us(PWM_MAX - pwm_idx);
    }
  }
}

// 測試模式
void check_test_mode(void) {
  if (ORB.TEST) {
    tDelay_ms = TEST_DELAY_MS;
  } else {
    tDelay_ms = TURN_DELAY_MS;
  }
}

// P2
void check_POS_P2(void) {
  if (ORB.POS) {
    P2_on();
  } else {
    P2_off();
  }
}

// 方向燈
void turn_on_turn_signals(void) {

  switch (eTurn_step) {
  // 有向方燈信號開始亮燈
  case TURN_STEP_0:
    if (ORB.TURN) {
      all_led_off();
      eTurn_step++;
      YLED01 = 1;
      YLED02 = 1;
      YLED06 = 1;
      turn_1ms_cnt = 0;
    }
    break;

  case TURN_STEP_1:
    if (turn_1ms_cnt >= tDelay_ms) {
      YLED03 = 1;
      YLED04 = 1;
      YLED07 = 1;
      eTurn_step++;
      turn_1ms_cnt = 0;
    }
    break;

  case TURN_STEP_2:
    if (turn_1ms_cnt >= tDelay_ms) {
      YLED05 = 1;
      YLED09 = 1;
      YLED08 = 1;
      eTurn_step++;
      turn_1ms_cnt = 0;
    }
    break;

  case TURN_STEP_3:
    if (turn_1ms_cnt >= tDelay_ms) {
      YLED10 = 1;
      eTurn_step++;
      turn_1ms_cnt = 0;
    }
    break;

  case TURN_STEP_4:
    // 直到方向燈信號OFF，關閉方向燈
    break;

  default:
    eTurn_step = TURN_STEP_0;
    turn_1ms_cnt = 0;
    break;
  }
}

// 賓迎燈
void check_welcome_light(void) {

  switch (eWelcome_step) {
  case WELCOME_STEP_0:
    all_led_off();
    eWelcome_step++;
    welcome_1ms_cnt = 0;
    break;

  // 流光分四段 前進
  case WELCOME_STEP_1:
    yellow_seg1_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_2:
    yellow_seg2_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_3:
    yellow_seg3_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_4:
    yellow_seg4_forward();
    delay_ms(II_CNT);
    eWelcome_step++;
    break;

  // 流光分四段 後退
  case WELCOME_STEP_5:
    tellow_seg1_backward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_6:
    yellow_seg2_backward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_7:
    yellow_seg3_backward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_8:
    yellow_seg4_backward();
    delay_ms(II_CNT);
    delay_ms(250);
    eWelcome_step++;
    break;

  // 流光分四段 前進
  case WELCOME_STEP_9:
    yellow_seg1_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_10:
    yellow_seg2_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_11:
    yellow_seg3_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_12:
    yellow_seg4_forward();
    delay_ms(II_CNT);
    eWelcome_step++;
    break;

  // 黃光轉白光
  case WELCOME_STEP_13:
    yellow_to_white();
    __delay_ms(II_CNT);
    __delay_ms(II_CNT);
    eWelcome_step++;
    break;

  // 時間到(15秒)LED OFF
  case WELCOME_STEP_14:
    // 接受觸發離開
     if(ORB.TURN||ORB.DRL||ORB.POS){
      fWelcome_light = 0;
      fWelcome_light_disable = 1;
      all_led_off();
    }

    if (welcome_1ms_cnt >= WELCOME_LIGHT_TOTAL_MS) {
      // 白光漸滅
      fWelcome_light = 0;
      fWelcome_light_disable = 1;
      white_fad_out();
    }
    break;

  default:
    break;
  }
}

// LED main
void LED_main(void) {
  // debounce IO
  if (f1ms) {
    f1ms = 0;
    debounce_IO();
    turn_signals_state_update();
    check_welcome_signal();
    check_test_mode();
    check_POS_P2();
  }

  // WELCOME LIGHT
  if (!fWelcome_light_disable && !ORB.TURN) {
    if (fWelcome_light) {
        check_welcome_light();
    }
  } else {
    eWelcome_step = WELCOME_STEP_0;
    fWelcome_light=0;
  }

  // turn signal
  if (!fturn_light_disable) {
    turn_on_turn_signals();
  } else {
    eTurn_step = TURN_STEP_0;
  }

  // DRL/POS
  if (fturn_off_600ms&&!fWelcome_light) {
    if (ORB.DRL) {
      DRL_on();
    } else if (ORB.POS) {
      POS_on();
    } else {
      all_led_off();
      fWelcome_light_disable = 0;
    }
  }
}