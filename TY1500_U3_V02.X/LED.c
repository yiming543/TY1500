/*
 * File:   LED.c
 * Author: T00904
 * MCU:PIC16F1936
 * 功能:控制DRL/POS/方向燈/迎賓燈
 * Created on January 8, 2026, 11:29 AM
 */

#include "LED.h"
#include <pic.h>
#include <stdint.h>

// RAM
uint16_t T1MS_cnt = 0;
uint16_t T1MS_WELCOME_cnt = 0;
uint16_t TdelayMS = TURN_DELAY_MS;
uint16_t TurnON_cnt = 0;
uint16_t TurnOff_cnt = 0;
sflag ORB, TRB;
bool fT1MS = 0;
bool fTURN_SIGNAL_OFF = 0;
bool fWelcomeLight = 0;
bool fWelcomeLight_disable = 0;
bool fTurnLightOff600ms = 0;

// 消除未呼叫警告 假裝有使用這些函數
void Clear_No_Call_Warning(void) {
  uint8_t i = 0;
  if (i == 1) {
    PWM_ALL_OFF();
  } else if (i == 2) {
    TMR0_ReadTimer();
    TMR0_WriteTimer(0);
    TMR0_ReadTimer();
    TMR0_WriteTimer(0);
    TMR0_Reload();
  } else if (i == 3) {
  } else if (i == 4) {
  } else if (i == 5) {
  } else if (i == 6) {
    TMR2_StartTimer();
    TMR2_StopTimer();
    TMR2_ReadTimer();
    TMR2_WriteTimer(0);
    TMR2_LoadPeriodRegister(0);
    TMR2_HasOverflowOccured();
  }
}

// 消除彈跳
void Debounce_IO(void) {
  uint8_t temp = 0;
  if (IsTurnSignal()) {
    temp |= BIT_TURN;
  }
  if (IsDRL()) {
    temp |= BIT_DRL;
  }
  if (IsPOS()) {
    temp |= BIT_POS;
  }
  if (IsWhite()) {
    temp |= BIT_WHITE;
  }
  if (IsTest()) {
    temp |= BIT_TEST;
  }
  if (temp ^ TRB.Byte) {
    TRB.Byte = temp;
  } else {
    ORB.Byte = temp;
  }
}

// 檢查方向燈信號
void CheckTurnSignals(void) {
  // 方向燈OFF超過600ms執行迎賓燈
  if (!ORB.TURN) {
    TurnOff_cnt++;
    if (TurnOff_cnt >= TURN_LIGHT_OFF_600MS) // 600ms
    {
      fTurnLightOff600ms = 1;
      TurnOff_cnt = TURN_LIGHT_OFF_600MS;
    }
  } else {
    TurnOff_cnt = 0;
    fTurnLightOff600ms = 0;
  }

  // 方向燈ON超過600ms啟動迎賓燈
  if (ORB.TURN) {
    TurnON_cnt++;
    if (TurnON_cnt >= TURN_LIGHT_ON_600MS) // 600ms
    {
      fWelcomeLight = 1;
      TurnON_cnt = TURN_LIGHT_ON_600MS;
    }
  } else {
    TurnON_cnt = 0;
  }

  // 有方向燈ON,重置信號
  if (ORB.TURN) {
    fTURN_SIGNAL_OFF = 0;
  }
}

// 所有黃光ON
void YLED_ALL_ON(void) {
  LATA |= 0xff;
  LATC |= 0x03;
}

// 所有黃光OFF
void YLED_ALL_OFF(void) {
  LATA &= 0x00;
  LATC &= 0xFC;
}

// 白光ON/OFF
void WLED_ALL_ON(void) { WLED01 = ON; }
void WLED_ALL_OFF(void) { WLED01 = OFF; }

// P2 ON/OFF
void P2_ON(void) { SideLight_SetHigh(); }
void P2_OFF(void) { SideLight_SetLow(); }

// PWM工作週期設定
void PWM_DRL(void) { EPWM1_LoadDutyValue(PWM1_DutyCycle_60PERCENT); }
void PWM_POS(void) { EPWM1_LoadDutyValue(PWM1_DutyCycle_6PERCENT); }
void PWM_TURN_LIGHT(void) { EPWM1_LoadDutyValue(PWM1_DutyCycle_100PERCENT); }
void PWM_ALL_OFF(void) { EPWM1_LoadDutyValue(0); }

// 畫行燈
void DRL_ON(void) {
  if (ORB.WHITE) {
    YLED_ALL_OFF();
  } else {
    WLED_ALL_OFF();
  }
  PWM_DRL();
  if (ORB.WHITE) {
    WLED_ALL_ON();
  } else {
    YLED_ALL_ON();
  }
}

// 位置燈
void POS_ON(void) {
  if (ORB.WHITE) {
    YLED_ALL_OFF();
  } else {
    WLED_ALL_OFF();
  }
  PWM_POS();
  if (ORB.WHITE) {
    WLED_ALL_ON();
  } else {
    YLED_ALL_ON();
  }
}

// 所有LED OFF
void ALL_LED_OFF(void) {
  YLED_ALL_OFF();
  WLED_ALL_OFF();
  PWM_TURN_LIGHT();
}

// 輸入
bool IsWhite(void) { return iYelowWhiteSelect_PORT; }
bool IsTurnSignal(void) { return iTurnSignal_PORT; }
bool IsTest(void) { return iTestPin_PORT; }
bool IsDRL(void) { return iDRL_PORT; }
bool IsPOS(void) { return iPOS_PORT; }

// TMR0中斷副程式10ms event
void TMR0_10MS_Even(void) {
  fT1MS = 1;
  T1MS_WELCOME_cnt++;
  T1MS_cnt++;
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
void YellowToWhite(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx >= 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < 50; ii++) {
      YLED_ALL_ON();
      WLED_ALL_OFF();
      delay_us(pwm_idx);
      YLED_ALL_OFF();
      WLED_ALL_ON();
      delay_us(PWM_MAX - pwm_idx);
    }
  }
  WLED_ALL_ON();
}

// 白光漸滅
void White_fad_out(void) {
  for (int8_t pwm_idx = PWM_MAX; pwm_idx >= 0; pwm_idx--) {
    if (iTurnSignal_PORT)
      break;
    for (uint8_t ii = 0; ii < 25; ii++) {
      WLED_ALL_ON();
      delay_us(pwm_idx);
      WLED_ALL_OFF();
      delay_us(PWM_MAX - pwm_idx);
    }
  }
}

// 黃光 第一段 前進
void Yellow_SEG1_forward(void) {
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
void Yellow_SEG2_forward(void) {
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
void Yellow_SEG3_forward(void) {
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
void Yellow_SEG4_forward(void) {
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
void Yellow_SEG1_backward(void) {
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
void Yellow_SEG2_backward(void) {
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
void Yellow_SEG3_backward(void) {
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
void Yellow_SEG4_backward(void) {
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
void CheckTestMode(void) {
  if (ORB.TEST) {
    TdelayMS = TEST_DELAY_MS;
  } else {
    TdelayMS = TURN_DELAY_MS;
  }
}

// P2
void CheckPOS_P2(void) {
  if (ORB.POS) {
    P2_ON();
  } else {
    P2_OFF();
  }
}

// 方向燈
void TurnOnTurnSignals(void) {
  static eTURN_STEP eTurn_step = TURN_STEP_0;

  // 方向燈信號OFF，關閉方向燈
  if (!ORB.TURN) {
    eTurn_step = TURN_STEP_0;
    if (!fTURN_SIGNAL_OFF) {
      fTURN_SIGNAL_OFF = 1;
      ALL_LED_OFF();
    }
  }

  switch (eTurn_step) {
  // 有向方燈信號開始亮燈
  case TURN_STEP_0:
    if (ORB.TURN) {
      ALL_LED_OFF();
      eTurn_step++;
      YLED01 = 1;
      YLED02 = 1;
      YLED06 = 1;
      T1MS_cnt = 0;
    }
    break;

  case TURN_STEP_1:
    if (T1MS_cnt >= TdelayMS) // 1000ms
    {
      YLED03 = 1;
      YLED04 = 1;
      YLED07 = 1;
      eTurn_step++;
      T1MS_cnt = 0;
    }
    break;

  case TURN_STEP_2:
    if (T1MS_cnt >= TdelayMS) // 1000ms
    {
      YLED05 = 1;
      YLED09 = 1;
      YLED08 = 1;
      eTurn_step++;
      T1MS_cnt = 0;
    }
    break;

  case TURN_STEP_3:
    if (T1MS_cnt >= TdelayMS) // 1000ms
    {
      YLED10 = 1;
      eTurn_step++;
      T1MS_cnt = 0;
    }
    break;

  case TURN_STEP_4:
    // 直到方向燈信號OFF，關閉方向燈
    break;

  default:
    eTurn_step = TURN_STEP_0;
    T1MS_cnt = 0;
    break;
  }
}

// 賓迎燈
void CheckWelcomeLight(void) {
  static eWELCOME_STEP eWelcome_step = WELCOME_STEP_0;

  if (ORB.TURN && eWelcome_step != WELCOME_STEP_0) {
    eWelcome_step = WELCOME_STEP_0;
    fWelcomeLight = 0;
    ALL_LED_OFF();
    return;
  }

  switch (eWelcome_step) {
  case WELCOME_STEP_0:
    if (fTurnLightOff600ms) {
      ALL_LED_OFF();
      eWelcome_step++;
      T1MS_WELCOME_cnt = 0;
    }
    break;

  // 流光分四段 前進
  case WELCOME_STEP_1:
    Yellow_SEG1_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_2:
    Yellow_SEG2_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_3:
    Yellow_SEG3_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_4:
    Yellow_SEG4_forward();
    delay_ms(II_CNT);
    eWelcome_step++;
    break;

  // 流光分四段 後退
  case WELCOME_STEP_5:
    Yellow_SEG1_backward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_6:
    Yellow_SEG2_backward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_7:
    Yellow_SEG3_backward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_8:
    Yellow_SEG4_backward();
    delay_ms(II_CNT);
    delay_ms(250);
    eWelcome_step++;
    break;

  // 流光分四段 前進
  case WELCOME_STEP_9:
    Yellow_SEG1_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_10:
    Yellow_SEG2_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_11:
    Yellow_SEG3_forward();
    eWelcome_step++;
    break;

  case WELCOME_STEP_12:
    Yellow_SEG4_forward();
    delay_ms(II_CNT);
    eWelcome_step++;
    break;

  // 黃光轉白光
  case WELCOME_STEP_13:
    YellowToWhite();
    __delay_ms(II_CNT);
    __delay_ms(II_CNT);
    eWelcome_step++;
    break;

  // 時間到(15秒)LED OFF
  case WELCOME_STEP_14:
    if (T1MS_WELCOME_cnt >= WELCOME_LIGHT_TOTAL_MS) {
      // 白光漸滅
      White_fad_out();
      T1MS_cnt = 0;
      T1MS_WELCOME_cnt = 0;
      fWelcomeLight = 0;
      eWelcome_step = WELCOME_STEP_0;
      fTurnLightOff600ms = 0;
      TurnOff_cnt = 0;
      fWelcomeLight_disable = 1;
    }
    break;

  default:
    break;
  }
}

// LED main
void LED_main(void) {
  // debounce IO
  if (fT1MS) {
    fT1MS = 0;
    Debounce_IO();
    CheckTurnSignals();
    CheckTestMode();
    CheckPOS_P2();
  }

  // WELCOME LIGHT
  if (!fWelcomeLight_disable) {
    if (fWelcomeLight) {
      CheckWelcomeLight();
    }
  } else {
    fWelcomeLight = 0;
  }

  // turn signal
  TurnOnTurnSignals();

  // DRL & POS
  if (!fWelcomeLight) {
    if (fTurnLightOff600ms) {
      // 沒有迎賓燈時，方向燈OFF超過600ms執行DRL或POS
      if (ORB.DRL) {
        DRL_ON();
        fWelcomeLight_disable = 1;
      } else if (ORB.POS) {
        POS_ON();
        fWelcomeLight_disable = 1;
      } else {
        ALL_LED_OFF();
        fWelcomeLight_disable = 0;
      }
    }
  }
}