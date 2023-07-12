/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 14:14:04
 * @LastEditTime: 2023-07-12 18:14:16
 */
#include "gui.h"

u8 lightOff = 0;
u8 lightLevel = 7;

void vfd_gui_init() {}

void vfd_gui_set_one_text(u8 index, char* oneChar) {
    vfd_gui_fonts* f;
    for (int i = 0; i < VFD_GUI_FONT_LEN; i++) {
        if (strcmp(oneChar, fonts[i].text) == 0) {
            f = &fonts[i];
            break;
        }
    }
    setModeWirteDisplayMode(0);               // command2
    sendDigAndData(index, f->font, 3);        // command3
    setDisplayMode(4);                        // command1
    ptSetDisplayLight(lightOff, lightLevel);  // command4
}
void vfd_gui_set_text(char* string) {
    if (sizeof(string) != 8) {
        Serial.println("string的长度必须是8位!");
        return;
    }

    u8 data[24];
    u8 index = 0;
    for (int i = 0; i < 8; i++) {
        for (int i = 0; i < VFD_GUI_FONT_LEN; i++) {
            if (strcmp(&string[i], fonts[i].text) == 0) {
                memcpy(data + index, fonts[i].font, 16);
                index += 8;
                memcpy(data + index, 0, 8);
                index += 24;
                break;
            }
        }
    }

    setModeWirteDisplayMode(0);  // command2
}