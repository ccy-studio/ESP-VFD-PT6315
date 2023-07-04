/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 14:33:25
 * @LastEditTime: 2023-07-04 17:27:20
 */
#ifndef __PT6315__
#define __PT6315__

#define PT_PLATFORM ESPMCU

#if PT_PLATFORM == ESPMCU
#include <Arduino.h>
#endif

#include "pt6305_fount.h"

#define CLK_PIN_GROUP 0
#define CLK_PIN GPIO_NUM_1
#define DIN_PIN_GROUP 0
#define DIN_PIN GPIO_NUM_2
#define STB_PIN_GROUP 0
#define STB_PIN GPIO_NUM_3

#define CLK_1 digitalWrite(CLK_PIN, HIGH)
#define CLK_0 digitalWrite(CLK_PIN, LOW)
#define DIN_1 digitalWrite(DIN_PIN, HIGH)
#define DIN_0 digitalWrite(DIN_PIN, LOW)
#define STB_1 digitalWrite(STB_PIN, HIGH)
#define STB_0 digitalWrite(STB_PIN, LOW)

#define delay_us(us) delayMicroseconds(us)

/**
 * 初始化GPIO
 */
void ptInitGPIO(void);

/**
 * 初始化
 * @param addressMode 地址模式 0自增, 1固定地址模式
 * @param digit 显示模式设置命令 ↓
 * 0000 ： 4位， 24段
 * 0001 ：5位， 23段
 * 0010 ： 6位数字， 22段
 * 0011 ： 7位， 21段
 * 0100 ： 8位， 20段
 * 0101 ： 9位， 19段
 * 0110 ： 10位， 18段
 * 0111 ： 11位， 17段
 * 1XXX ： 12位， 16段
 */
void ptInitialSetting(uint8_t addressMode, uint8_t digit);

/**
 * 显示控制命令  COMMANDS 4
 * @param onOff 0显示关闭，1开启显示
 * @param brightnessVal 亮度占空比 0~7调整
 * 000：脉冲宽度= 1/16 0
 * 001：脉冲宽度= 2/16 1
 * 010 ：脉冲宽度= 4/16 0x2
 * 011 ：脉冲宽度= 10/16 3
 * 100：脉冲宽度= 11/16  4
 * 101 ：脉冲宽度= 12/16 0x5
 * 110：脉冲宽度= 13/16 6
 * 111：脉冲宽度= 14/16 0x7
 */
void ptSetDisplayLight(uint8_t onOff, uint8_t brightnessVal);

void ptWriteRam(uint8_t startAddress, uint8_t dataArr[3]);
void ptPrintOne(int index, char ascii);
void ptPrintString(int index, char* strAscii);
#endif