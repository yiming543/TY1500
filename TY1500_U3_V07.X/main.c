/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules
  selected in the GUI. Generation Information : Product Revision  :  PIC10 /
  PIC12 / PIC16 / PIC18 MCUs - 1.81.8 Device            :  PIC16F1936 Driver
  Version    :  2.00
*/


// 20260109 V01 CS:
// IC1(IBV363) 第一次啟動時enable腳位要送100%的PWM值，之後再依需求調整PWM值
// PWM 625HZ
// 1.方向燈OK
// 2.位置燈OK
// 3.日行燈OK
// 4.P2 OK
// 5.白黃切換OK (行車&晝行燈白光或黃光)
// 6.TEST POINT OK(短路方向燈速度變慢)

//20260127 V02 CS:BE1D
//1.有POS信號P2就亮.
//2.方向燈流光 有方向燈信號就作動.(沒有方向燈信號時，立刻關閉方向燈)
//3.迎賓燈 方向燈信號超過600ms,再等待600ms無方向燈信號作動.(有方向燈信號時，立刻停止迎賓燈)
//4.DRL/POS 無迎賓燈旗標，沒有方向燈信號超過600ms才作動.
//5.IC1(IBV363) 維持在PWM 100%(PWM 0%時，無法啟動)
//6.DRL/POS 啟動後就不要再跑迎賓燈了.
//7.DRL/POS 關閉 重置迎賓燈功能)
//8.迎賓燈只能跑一次.

//20260130 V03 CS:E3B3
//修正變數 函數名稱

//20260304 V04 CS:72DE
//迎賓燈改用unlcok做觸發.

//20260305 V05 CS:D5F8
//修正迎賓燈一直送會重覆啟動迎賓燈

//20260306 V06 CS:C1F6
//1.因為AUTO白天模式沒有送出unlock信號，所以改用方向燈2次啟動迎賓燈
//2.等方向燈停止600ms才能啟動DRL/POS，避免迎賓燈和DRL/POS同時作動
//3.等方向燈停止600ms,判斷迎賓燈條件是否成立.
//4.迎賓結束後，需等DRL/POS沒有訊號才能再度使用迎賓燈.

//20260327 TY1500_U3_V07 CS:31B0
//修正POS PWM duty 6% LED 微閃爍問題
//PWM頻率由688HZ 改為 250HZ(driver IC接收最大頻率500HZ)

//20260331 TY1500_U3_V08 CS:4EF5
//先前方向燈接線順序焊接錯誤，修改LED點燈順序.
//方向燈由4段改成7段.
//迎賓燈由4段改成7段.
//200ms內方向燈全亮




#include "LED.h"
#include <xc.h>
#include <stdint.h>

// extern void LED_main(void);

/*
                         Main application
 */
int main(void) {
  // initialize the device
  SYSTEM_Initialize();
  TMR0_SetInterruptHandler(tmr0_10ms_even);

//  all_led_off();
  clear_no_call_warning_message();
  LED_en = 1; // enable LED driver
  
  // Enable the Global Interrupts
  INTERRUPT_GlobalInterruptEnable();
  // Enable the Peripheral Interrupts
  INTERRUPT_PeripheralInterruptEnable();

  while (1) {
    // Add your application code
    LED_main();
  }
  return 0;
}
/**
 End of File
*/