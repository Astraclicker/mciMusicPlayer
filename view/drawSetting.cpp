#include "drawMain.h"
#include "drewSetting.h"

void setVolume(int v) {
    //边界处理
    if (v < 0) v = 0;
    if (v > 100) v = 100;
    volume = v;
    //设置音量
    char cmd[100];
    sprintf(cmd, "setaudio %s volume to %d", deviceName.c_str(), v * 10);
    mciSendString(cmd, NULL, 0, NULL);
}


void drawSetting() {
    BeginBatchDraw();
    setting.drawButton();
    if (exit_setting.checkButton(msg.x, msg.y)) {
        exit_setting_on.drawButton();
    } else {
        exit_setting.drawButton();
    }

    if (spectrum_setting.checkButton(msg.x, msg.y)) {
        spectrum_setting_on.drawButton();
    } else {
        spectrum_setting.drawButton();
    }
    switch (vol_flag) {
        //根据值 改变play_mode的状态
        case true:
            if (volOn.checkButton(msg.x, msg.y)) {
                volOn_on.drawButton();
            } else {
                volOn.drawButton();
            }
            break;
        case false:
            if (volOff.checkButton(msg.x, msg.y)) {
                volOff_on.drawButton();
            } else {
                volOff.drawButton();
            }
            break;
    }
    /*
     *画出音乐音量条
     *负责人：凉雨
    */
    sliderX = volume * 2 + 350;
    outtextxy(200, 340, "音量:");
    // 绘制音量滑块轨道
    rectangle(350, 350, 550, 355);

    // 绘制填充部分（蓝色）
    setfillcolor(RGB(38, 120, 255));
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
