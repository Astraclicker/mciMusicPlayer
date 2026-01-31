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
//音量
button_img vol(300,330,base_vol,"sources/image/audio_modes/btn_volume_on_down.png");
button_img vol_on(300,330,base_vol_on,"sources/image/audio_modes/btn_volume_on_down.png");

//1.滑块的坐标和点击状态
int sliderX=470;
bool dragging = false;
//2.MCI音量调节
void setVloume(int v) {
    //边界处理
    if (v<0) v=0;
    if (v>100) v=100;
    volume=v;
    //设置音量
    char cmd[100];
    sprintf(cmd, "setaudio myaudio volume to %d", v * 10);
    mciSendString(cmd, NULL, 0, NULL);
}

//3.画出设置界面
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

    if (vol.checkButton(msg.x,msg.y)) {
       vol_on.drawButton();
    }else {
        vol.drawButton();
    }
    //画出音乐音量条
    //负责人：凉雨
    outtextxy(200,340,"音量:");
    // 绘制音量滑块轨道
    rectangle(350, 350, 550, 355);

    // 绘制填充部分（蓝色）
    setfillcolor(RGB(38,120,255));
    fillrectangle(350, 350, sliderX, 355);

    // 绘制滑块
    // // 2. 画白色内圆
     setfillcolor(WHITE);
     solidcircle(sliderX, 352.5, 8);
    // 显示音量数值
    char volText[20];
    sprintf(volText, "%d%%", volume);
    outtextxy(560, 335, volText);

    FlushBatchDraw();



    EndBatchDraw();
}

