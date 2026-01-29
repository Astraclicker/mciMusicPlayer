#ifndef MCIMUSICPLAYER_START_H
#define MCIMUSICPLAYER_START_H
#include <easyx.h>
#include "view/drawMain.h"
#include "view/drewSetting.h"
#include "service/def.h"
#include <iostream>
using std::cout;
using std::endl;
void start() {
    initgraph(width_window, length_window);
    condition = statu::main;
    drawMain();



    while (true) {
        switch (condition) {
            case statu::main:
                drawMain();
                getmessage(&msg,EX_MOUSE);
                //单击设置
                if (msg.message == WM_LBUTTONDOWN && button_setting.checkButton(msg.x, msg.y)) {
                    cout<<"设置"<<endl;
                    condition = statu::setting;
                    flushmessage(EX_MOUSE);
                }

                //单击暂停/播放
                if (msg.message == WM_LBUTTONDOWN && button_pause.checkButton(msg.x, msg.y)) {
                    cout<<"播放暂停"<<endl;
                }

                //单击回退
                if (msg.message == WM_LBUTTONDOWN && button_backward.checkButton(msg.x, msg.y)) {
                    cout<<"回退"<<endl;
                }

                //单击快进
                if (msg.message == WM_LBUTTONDOWN && button_forward.checkButton(msg.x,msg.y)) {
                    cout<<"快进"<<endl;
                }

                //单击上一曲
                if (msg.message == WM_LBUTTONDOWN && button_previous.checkButton(msg.x,msg.y)) {
                    cout<<"上一曲"<<endl;
                }

                //单击下一曲
                if (msg.message == WM_LBUTTONDOWN && button_next.checkButton(msg.x,msg.y)) {
                    cout<<"下一曲"<<endl;
                }
                break;


            case statu::setting:
                drawSetting();
                getmessage(&msg);
                //按下esc
                if (msg.message == WM_KEYDOWN) {
                    if (msg.message == 256) {
                        condition = statu::main;
                    }
                }
                //按下鼠标
                else if (msg.message == WM_LBUTTONDOWN) {
                    cout<<msg.x<<"||"<<msg.y<<endl;

                    if (exit_setting.checkButton(msg.x,msg.y)) {
                        condition = statu::main;
                    }
                    if (spectrum_setting.checkButton(msg.x,msg.y)) {
                        system("start sources/cava/cava.exe");
                    }
                }
                flushmessage();
                break;


        }
    }

}
#endif