#pragma once
#include <easyx.h>
#include "../function/button.h"
#include "base.h"


//设置界面
button_color setting(width_window/8,length_window/8,base_setting);
//退出设置
button_txt exit_setting(190,140,"退出",base_function_setting,CN);
button_txt exit_setting_on(190,140,"退出",base_function_setting_on,CN);
//打开频谱
button_txt spectrum_setting(190,220,"频谱",base_function_setting,CN);
button_txt spectrum_setting_on(190,220,"频谱",base_function_setting_on,CN);
//音量打开
button_img volOn(300,330,base_vol,"sources/image/audio_modes/btn_volume_on_down.png");
button_img volOn_on(300,330,base_vol_on,"sources/image/audio_modes/btn_volume_on_hover.png");
//音量关闭
button_img volOff(300,330,base_vol,"sources/image/audio_modes/btn_mute_down.png");
button_img volOff_on(300,330,base_vol_on,"sources/image/audio_modes/btn_mute_hover.png");
//声明设备名称
std::string deviceName="myaudio";
//滑块的坐标和点击状态
int sliderX=470;
bool dragging = true;
bool vol_flag = true;
//MCI音量调节
void setVloume(int v) {
    //边界处理
    if (v<0) v=0;
    if (v>100) v=100;
    volume=v;
    //设置音量
    char cmd[100];
    sprintf(cmd, "setaudio %s volume to %d",deviceName.c_str() ,v * 10);
    mciSendString(cmd, NULL, 0, NULL);
}

//画出设置界面
void drawSetting () {
    BeginBatchDraw();
    setting.drawButton();
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
    switch (vol_flag) {//根据值 改变play_mode的状态
        case true:
            if (volOn.checkButton(msg.x,msg.y)) {
                volOn_on.drawButton();
            }else {
                volOn.drawButton();
            }
            break;
        case false:
            if (volOff.checkButton(msg.x,msg.y)) {
                volOff_on.drawButton();
            }else {
                volOff.drawButton();
            }
            break;
    }
    /*
     *画出音乐音量条
     *负责人：凉雨
    */
    outtextxy(200,340,"音量:");
    // 绘制音量滑块轨道
    rectangle(350, 350, 550, 355);

    // 绘制填充部分（蓝色）
    setfillcolor(RGB(38,120,255));
    fillrectangle(350, 350, sliderX, 355);

    // 绘制滑块
    // 画白色内圆
     setfillcolor(WHITE);
     solidcircle(sliderX, 352.5, 8);
    // 显示音量数值
    char volText[20];
    sprintf(volText, "%d%%", volume);
    outtextxy(560, 335, volText);

    FlushBatchDraw();
    EndBatchDraw();
}

