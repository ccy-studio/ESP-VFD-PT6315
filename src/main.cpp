/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 11:49:31
 * @LastEditTime: 2023-07-12 23:52:25
 */
#include <Arduino.h>
#include <gui.h>

#define LED_PIN 15
#define PWM_PIN 13

u8 colon = 0;

void task1(void* pvParameters) {
    while (1) {
        delay(500);
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    // 设置PWM的频率单位hz
    analogWriteFreq(10000);
    pinMode(LED_PIN, OUTPUT);
    pinMode(PWM_PIN, OUTPUT);
    analogWrite(PWM_PIN, 128);

    ptInitGPIO();
    Serial.println("Init Success!");
    vfd_gui_init();

    vfd_gui_set_text("Connect");
    
}

void loop() {
    delay(500);
    // digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    vfd_gui_set_colon(colon);
    colon = !colon;
}
