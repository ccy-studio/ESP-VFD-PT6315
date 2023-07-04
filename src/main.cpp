/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 11:49:31
 * @LastEditTime: 2023-07-04 17:29:55
 */
#include <Arduino.h>
#include "pt6315.h"

void setup() {
    Serial.begin(115200);
    ptInitGPIO();
    ptInitialSetting(0, 0x5);
    ptSetDisplayLight(1, 7);

    printf("Init Success!\n");
}

void loop() {
    uint8_t arr[3] = {0xff, 0xff, 0xff};
    ptWriteRam(0, arr);
    ptWriteRam(3, arr);
    ptWriteRam(6, arr);
    delay(100);
}
