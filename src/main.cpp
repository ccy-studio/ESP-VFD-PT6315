/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-04 11:49:31
 * @LastEditTime: 2023-07-14 16:06:34
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

WiFiManager wifiManager;
u32 k1_last_time = 0; //按键1的上一次按下触发时间记录
tm timeinfo;
String time_str = String();

// 0=年月日,1等于时分秒
u8 gui_page = 1;
// 时分秒的样式 0 默认 HH:mm; 1 HH:mm:ss
u8 gui_page_1_style = 0;

u8 wifi_conn = 0; //标记wifi是否链接成功的状态

u32 key_filter_sec = 0;  // 按键防抖
u8 last_key_pin = 0; //记录上一次点击的按键PIN码

IRAM_ATTR void handleKeyInterrupt();
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
    delay(3000);
    vfd_gui_init();
    vfd_gui_set_text("wifi....");

    printf("WIFI SSID:%s\n", wifiManager.getWiFiSSID().c_str());
    printf("WIFI PWD:%s\n", wifiManager.getWiFiPass().c_str());

    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setCountry("CN");
    wifiManager.setBreakAfterConfig(true);
    wifiManager.setTimeout(60);
    // wifiManager.setDebugOutput(false);
    String ssid = "VFD-" + String(ESP.getChipId());
    if (!wifiManager.autoConnect(ssid.c_str(), NULL)) {
        Serial.println("Failed to connect and hit timeout.");
        while (1) {
            //如果AP超时后就循环闪烁LED并VFD显示超时信息
            delay(500);
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            vfd_gui_set_text("timeout.");
        }
    }

    // 配网成功，打印连接信息
    Serial.println("Connected to WiFi!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    wifi_conn = 1;

    //到这里程序WIFI链接成功，获取时间提示显示加载文字。
    digitalWrite(LED_PIN, HIGH);
    vfd_gui_clear();
    vfd_gui_set_text("loading.");
    getTimeInfo();
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
                time_str += timeinfo.tm_hour;
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
        vfd_gui_set_text(time_str.c_str());
        vfd_gui_set_colon(colon);
    } else {
        // Wifi断开
        vfd_gui_set_text("wififail");
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}

IRAM_ATTR void handleKeyInterrupt() {
    u32 filter_sec = (micros() - key_filter_sec) / 1000;
    if (filter_sec < 500) {
        return;
    }
    if (!digitalRead(KEY1_PIN)) {
        // typec一侧的按键
        k1_last_time = micros();
        last_key_pin = KEY1_PIN;
    } else if (digitalRead(KEY1_PIN)) {
        // 低电平
        u32 sec = (micros() - k1_last_time) / 1000;
        if (k1_last_time != 0 && sec > 2000 && last_key_pin == KEY1_PIN) {
            // 如果长按到松下有2秒,执行重置WIFI的操作
            wifiManager.erase();
            //重启
            ESP.restart();
        } else {
            k1_last_time = 0;
        }
    }
    if (!digitalRead(KEY2_PIN)) {
        gui_page = !gui_page;
        k1_last_time = 0;
        last_key_pin = KEY2_PIN;
    }
    if (!digitalRead(KEY3_PIN)) {
        gui_page_1_style = !gui_page_1_style;
        k1_last_time = 0;
        last_key_pin = KEY3_PIN;
    }
    key_filter_sec = micros();
}

void configModeCallback(WiFiManager* myWiFiManager) {
    //如果发生配网的条件触发此方法
    Serial.println("Entered config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());
    //将LED点亮提示正在配网
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