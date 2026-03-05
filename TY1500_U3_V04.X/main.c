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

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software
   and any derivatives exclusively with Microchip products. It is your
   responsibility to comply with third party license terms applicable to your
   use of third party software (including open source software) that may
   accompany Microchip software.

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


#include "LED.h"
#include <pic.h>
#include <stdint.h>

/*
                         Main application
 */
int main(void) {
  // initialize the device
  SYSTEM_Initialize();
  TMR0_SetInterruptHandler(tmr0_10ms_even);

  // Enable the Global Interrupts
  INTERRUPT_GlobalInterruptEnable();
  // Enable the Peripheral Interrupts
  INTERRUPT_PeripheralInterruptEnable();

  all_led_off();
  clear_no_call_warning_message();
  LED_en = 1; // enable LED driver
  while (1) {
    // Add your application code
    LED_main();
  }
  return 0;
}
/**
 End of File
*/