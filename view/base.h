#ifndef MCIMUSICPLAYER_BASE_H
#define MCIMUSICPLAYER_BASE_H
#include "../function/button.h"
#include <easyx.h>
//初始化消息
ExMessage msg;

//构建一个功能基础按钮
inline button base_function(50, 50,WHITE, button_style::roundrect);
inline button base_function_setting(50,70,0x808080,button_style::roundrect);
inline button base_vol(40,40,0x808080,button_style::roundrect);
inline button base_vol_on(40,40,WHITE,button_style::roundrect);
inline button base_function_setting_on(50,70,WHITE,button_style::roundrect);
//构建文本类
inline txt CN(0, 0, 0xd4a74c, "FZCuYuan-M03");

#endif //MCIMUSICPLAYER_BASE_H