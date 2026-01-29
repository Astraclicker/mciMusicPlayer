#pragma once
#include "button1.h"
#include <easyx.h>
//构建一个功能基础按钮
inline button1 base_function(60, 60,40,100,WHITE, button_style::roundrect);

//构建文本类
inline txt CN(0,0,0xfcf7f1,"FZCuYuan-M03");

//初始化按钮
inline button_img button_setting(30,30,40,100,"sources/image/files_ui/btn_settings_down.png");
inline button_img button_pause(490,650,40,100,"sources/image/control/btn_pause_down.png");

void drawMain() {
    BeginBatchDraw();
    loadimage(NULL,bk_img.c_str());
    button_setting.drawButton();
    button_pause.drawButton();
    FlushBatchDraw();
    EndBatchDraw();
}