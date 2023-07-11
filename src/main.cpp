/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 11:49:31
 * @LastEditTime: 2023-07-12 00:30:12
 */
#include <Arduino.h>
#include "pt6315.h"

#define LED_PIN 15
#define PWM_PIN 13

void setup() {
    Serial.begin(115200);
    Serial.println("Start!");
    delay(2000);
    // 设置PWM的频率单位hz
    analogWriteFreq(10000);
    pinMode(LED_PIN, OUTPUT);
    pinMode(PWM_PIN, OUTPUT);
    analogWrite(PWM_PIN, 128);

    ptInitGPIO();
    testInit();
    Serial.println("Init Success!");
}

void loop() {
    test();
    delay(500);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
