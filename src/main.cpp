/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 11:49:31
 * @LastEditTime: 2023-07-04 22:46:26
 */
#include <Arduino.h>
#include "pt6315.h"
// #include "vfd.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Start!");
    delay(2000);
    // 设置PWM的频率单位hz
    analogWriteFrequency(12000);
    pinMode(GPIO_NUM_6, OUTPUT);
    analogWrite(GPIO_NUM_6, 128);

    ptInitGPIO();
    testInit();

    // // 初始化VFD
    // VFD_Init();
    // VFD_Clear();
    // VFD_ClearAD();
    // VFD_SetString(0, "Initializing");
    // VFD_SetDisplayOnOff(DISPLAY_ON);
    Serial.println("Init Success!");
}

void loop() {
    test();
}
