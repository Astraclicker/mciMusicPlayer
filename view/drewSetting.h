#pragma once
#include <easyx.h>
#include "../function/button.h"
#include "base.h"

//退出设置
button_txt exit_setting(190,140,"退出",base_function_setting,CN);
button_txt exit_setting_on(190,140,"退出",base_function_setting_on,CN);
//打开频谱
button_txt spectrum_setting(190,220,"频谱",base_function_setting,CN);
button_txt spectrum_setting_on(190,220,"频谱",base_function_setting_on,CN);

//画出设置界面
void drawSetting () {
    setfillcolor(0x808080);
    BeginBatchDraw();
    solidroundrect(width_window/8,length_window/8,width_window-width_window/8,length_window-length_window/8,10,10);


    if (exit_setting.checkButton(msg.x,msg.y)) {
        exit_setting_on.drawButton();
    }else {
        exit_setting.drawButton();
    }

    if (spectrum_setting.checkButton(msg.x,msg.y)) {
        spectrum_setting_on.drawButton();
    }else {
        spectrum_setting.drawButton();
    }

    //画出音乐音量条
    //负责人：凉雨

    FlushBatchDraw();
    EndBatchDraw();
}