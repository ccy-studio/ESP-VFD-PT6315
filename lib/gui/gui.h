/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 14:11:16
 * @LastEditTime: 2023-07-12 18:01:55
 */
#ifndef __VFD_GUI_
#define __VFD_GUI_

#include "pt6315.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define VFD_GUI_FONT_LEN 36

typedef struct {
    u8 font[2];
    char* text;
} vfd_gui_fonts;

extern vfd_gui_fonts fonts[VFD_GUI_FONT_LEN];

void vfd_gui_init();
void vfd_gui_set_one_text(u8 index, char* oneChar);
void vfd_gui_set_text(char* string);

#endif