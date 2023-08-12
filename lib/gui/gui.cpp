/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 14:14:04
 * @LastEditTime: 2023-08-13 00:33:00
 */
#include "gui.h"

extern vfd_gui_fonts fonts[VFD_GUI_FONT_LEN];

u8 lightOff = 1;    // 背光开关
u8 lightLevel = 7;  // 亮度级别

// 标记-DIG4的RAM数据-实时更新
static u8 dig4_colon_flag = 0;

void vfd_gui_init() {
    vfd_gui_clear();
}

void vfd_gui_clear() {
    dig4_colon_flag = 0;
    setModeWirteDisplayMode(0);  // command2
    u8 clearBuf[24];
    memset(clearBuf, 0x00, sizeof(clearBuf));
    setModeWirteDisplayMode(0);               // command2
    sendDigAndData(0, clearBuf, 24);          // command3
    setDisplayMode(4);                        // command1
    ptSetDisplayLight(lightOff, lightLevel);  // command4
}

void vfd_gui_set_one_text(size_t index, char oneChar) {
    u8 buf[3];
    memset(buf, 0, sizeof(buf));
    for (size_t i = 0; i < VFD_GUI_FONT_LEN; i++) {
        if (fonts[i].text == oneChar || (fonts[i].text + 32) == oneChar) {
            buf[0] = fonts[i].font[0];
            buf[1] = fonts[i].font[1];
            buf[2] = 0x00;
            break;
        }
    }
    if (index == 3) {
        // DIG4
        dig4_colon_flag = buf[1];
    }
    setModeWirteDisplayMode(0);               // command2
    sendDigAndData(index * 3, buf, 3);        // command3
    setDisplayMode(4);                        // command1
    ptSetDisplayLight(lightOff, lightLevel);  // command4
}

void vfd_gui_set_text(const char* string) {
    size_t str_len = strlen(string);
    if (str_len > 8) {
        printf("长度不可以大于8位可显示的区域!");
        return;
    }
    u8 data[24];
    memset(data, 0, sizeof(data));
    size_t index = 0;
    for (size_t i = 0; i < str_len; i++) {
        for (size_t j = 0; j < VFD_GUI_FONT_LEN; j++) {
            if (string[i] == fonts[j].text ||
                string[i] == (fonts[j].text + 32)) {
                data[index++] = fonts[j].font[0];
                data[index++] = fonts[j].font[1];
                data[index++] = 0x00;
                break;
            }
        }
    }
    if (str_len >= 4) {
        dig4_colon_flag = data[10];
    } else {
        dig4_colon_flag = 0;
    }
    setModeWirteDisplayMode(0);               // command2
    sendDigAndData(0, data, 24);              // command3
    setDisplayMode(4);                        // command1
    ptSetDisplayLight(lightOff, lightLevel);  // command4
}

void vfd_gui_set_colon(u8 display_state) {
    u8 command = dig4_colon_flag;
    if (display_state) {
        // 点亮冒号
        command |= 0x20;
    }
    setModeWirteDisplayMode(1);               // command2
    sendDigAndData(0x0A, &command, 1);        // command3
    setDisplayMode(4);                        // command1
    ptSetDisplayLight(lightOff, lightLevel);  // command4
}

void vfd_gui_set_bck(u8 onOff) {
    lightOff = onOff;
}

/**
 * 设置亮度等级 1~7
 */
void vfd_gui_set_blk_level(size_t level) {
    lightLevel = level;
}