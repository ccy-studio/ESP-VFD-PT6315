/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 11:49:31
 * @LastEditTime: 2023-07-13 15:18:13
 */
#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <gui.h>

#define LED_PIN 15
#define PWM_PIN 13

#define KEY1_PIN 5
#define KEY2_PIN 4
#define KEY3_PIN 2

#define NTP1 "ntp1.aliyun.com"
#define NTP2 "ntp2.aliyun.com"
#define NTP3 "ntp3.aliyun.com"

// VFD冒号显示标记
u8 colon = 0;
// 背光开关状态
u8 display_bck = 1;

WiFiManager wifiManager;
u32 k1_last_time = 0;
tm timeinfo;
String time_str = String();

// 0=年月日,1等于时分秒
u8 gui_page = 1;
// 时分秒的样式 0 默认 HH:mm; 1 HH:mm:ss
u8 gui_page_1_style = 0;

u8 wifi_conn = 0;

void handleKeyInterrupt();
void configModeCallback(WiFiManager* myWiFiManager);
void getTimeInfo();

void setup() {
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    pinMode(PWM_PIN, OUTPUT);

    pinMode(KEY1_PIN, INPUT);
    pinMode(KEY2_PIN, INPUT);
    pinMode(KEY3_PIN, INPUT);
    ptInitGPIO();

    // 注册按键中断函数
    attachInterrupt(digitalPinToInterrupt(KEY1_PIN), handleKeyInterrupt,
                    CHANGE);
    attachInterrupt(digitalPinToInterrupt(KEY2_PIN), handleKeyInterrupt,
                    CHANGE);
    attachInterrupt(digitalPinToInterrupt(KEY3_PIN), handleKeyInterrupt,
                    CHANGE);

    // 设置PWM的频率单位hz
    analogWriteFreq(10000);
    analogWrite(PWM_PIN, 128);
    // 默认点亮LED
    digitalWrite(LED_PIN, LOW);

    // 初始化VFD
    delay(2000);
    vfd_gui_init();
    vfd_gui_set_text("wifi....");

    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setBreakAfterConfig(true);
    wifiManager.setMinimumSignalQuality(10);
    // wifiManager.setDebugOutput(false);
    String ssid = "VFD-" + String(ESP.getChipId());
    if (!wifiManager.autoConnect(ssid.c_str(), NULL)) {
        Serial.println("Failed to connect and hit timeout.");
        delay(3000);
        // 重启ESP8266
        ESP.restart();
        delay(5000);
    }

    // 配网成功，打印连接信息
    Serial.println("Connected to WiFi!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    wifi_conn = 1;

    digitalWrite(LED_PIN, HIGH);
    vfd_gui_clear();
    vfd_gui_set_text("Request.");
}

void loop() {
    delay(500);
    // Set VFD Text
    time_str.clear();
    getTimeInfo();
    if (wifi_conn) {
        if (gui_page) {
            // 显示时间
            if (gui_page_1_style) {
                time_str += ">>";
                time_str += (timeinfo.tm_hour < 10 ? "0" : "");
                time_str += (timeinfo.tm_min < 10 ? "0" : "");
                time_str += timeinfo.tm_min;
                time_str += "<<";
                colon = !colon;
            } else {
                time_str += (timeinfo.tm_hour < 10 ? "0" : "");
                time_str += timeinfo.tm_hour;
                time_str += (timeinfo.tm_min < 10 ? ":0" : ":");
                time_str += timeinfo.tm_min;
                time_str += (timeinfo.tm_sec < 10 ? ":0" : ":");
                time_str += timeinfo.tm_sec;
                colon = 0;
            }

        } else {
            // 显示年月日
            time_str += (timeinfo.tm_year + 1900);
            // 补零月份
            if ((timeinfo.tm_mon + 1) < 10) {
                time_str += "0";
            }
            time_str += (timeinfo.tm_mon + 1);
            // 补零日期
            if (timeinfo.tm_mday < 10) {
                time_str += "0";
            }
            time_str += timeinfo.tm_mday;
            colon = 0;
        }
        vfd_gui_clear();
        vfd_gui_set_text(time_str.c_str());
        vfd_gui_set_colon(colon);
    } else {
        // Wifi断开
        vfd_gui_clear();
        vfd_gui_set_text("wififail");
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}

void handleKeyInterrupt() {
    if (digitalRead(KEY1_PIN)) {
        // typec一侧的按键
        k1_last_time = micros();
        display_bck = !display_bck;
        vfd_gui_set_bck(display_bck);
    } else {
        // 低电平
        u8 sec = (micros() - k1_last_time) / 1000;
        if (sec >= 2000) {
            // 如果长按到松下有2秒,执行重置WIFI的操作
            display_bck = 1;
            colon = 0;
            vfd_gui_set_bck(display_bck);
            vfd_gui_clear();
            wifiManager.resetSettings();
            vfd_gui_set_text("cleared.");
            Serial.println("WiFi settings cleared.");
            for (int i = 0; i < 3; i++) {
                digitalWrite(LED_PIN, !digitalRead(LED_PIN));
                delay(200);
            }
            vfd_gui_clear();
            vfd_gui_set_text("restart.");
            ESP.restart();
        }
    }
    if (digitalRead(KEY2_PIN)) {
        gui_page = !gui_page;
    }
    if (digitalRead(KEY3_PIN)) {
        gui_page_1_style = !gui_page_1_style;
    }
}

void configModeCallback(WiFiManager* myWiFiManager) {
    Serial.println("Entered config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());
    digitalWrite(LED_PIN, LOW);
    vfd_gui_clear();
    vfd_gui_set_text("config..");
}

void getTimeInfo() {
    if (!getLocalTime(&timeinfo)) {
        if (WiFi.isConnected()) {
            configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
        } else {
            wifi_conn = 0;
        }
    }
}