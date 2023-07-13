/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 14:11:16
 * @LastEditTime: 2023-07-13 14:50:25
 */
#ifndef __VFD_GUI_
#define __VFD_GUI_

#include "pt6315.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define VFD_GUI_FONT_LEN 43

typedef struct {
    u8 font[2];
    char text;
} vfd_gui_fonts;


void vfd_gui_init();
void vfd_gui_clear();
void vfd_gui_set_one_text(size_t index, char oneChar);
void vfd_gui_set_text(const char* string);
void vfd_gui_set_colon(u8 display_state);
void vfd_gui_set_bck(u8 onOff);

#endif