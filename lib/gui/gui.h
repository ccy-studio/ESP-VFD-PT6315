/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 14:11:16
 * @LastEditTime: 2023-07-14 16:12:57
 */
#ifndef __VFD_GUI_
#define __VFD_GUI_

#include "pt6315.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define VFD_GUI_FONT_LEN 43

//字体结构体
typedef struct {
    u8 font[2];
    char text;
} vfd_gui_fonts;


/**
 * 初始化
*/
void vfd_gui_init();
/**
 * 清空VFD屏幕显示,循环刷新如果使用vfd_gui_set_text方法不需要使用它。
*/
void vfd_gui_clear();
/**
 * 在指定位置显示一个char字符,index从0~7 8位
*/
void vfd_gui_set_one_text(size_t index, char oneChar);
/**
 * 显示一串文字，从0位开始。 不足8位补零(清空显示，方便每次不用调用clear防止闪屏出现)
*/
void vfd_gui_set_text(const char* string);
/**
 * 屏幕中间冒号的显示开关，1显示，0熄灭
*/
void vfd_gui_set_colon(u8 display_state);
/**
 * 背光开关
*/
void vfd_gui_set_bck(u8 onOff);

/**
 * 设置亮度等级 1~7
 */
void vfd_gui_set_blk_level(size_t level);
#endif