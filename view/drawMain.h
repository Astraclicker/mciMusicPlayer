#pragma once
#include "../function/button.h"
#include <easyx.h>
//构建一个功能基础按钮
inline button base_function(50,50,WHITE, button_style::roundrect);
//左宽右高
//构建文本类
inline txt CN(0,0,0xfcf7f1,"FZCuYuan-M03");

//初始化按钮

//设置
inline button_img button_setting(30,30,base_function,"sources/image/files_ui/btn_settings_down.png");
//播放
inline button_img button_pause(490,650,base_function,"sources/image/control/btn_pause_norm.png");
//回退
inline button_img button_backward(490-wid ,650,base_function,"sources/image/control/btn_backward_norm.png");
//快进
inline button_img button_forward(490+wid,650,base_function,"sources/image/control/btn_forward_norm.png");
//下一首
inline button_img button_next(490+2*wid,650,base_function,"sources/image/control/btn_next_norm.png");
//上一首
inline button_img button_previous(490-wid*2,650,base_function,"sources/image/control/btn_prev_norm.png");

//画出主界面
inline void drawMain() {
    BeginBatchDraw();
    loadimage(NULL,bk_img.c_str());

    /*
     * 按钮
     */
    button_setting.drawButton();
    button_pause.drawButton();
    button_backward.drawButton();
    button_forward.drawButton();
    button_next.drawButton();
    button_previous.drawButton();
    //展示
    FlushBatchDraw();
    EndBatchDraw();
}