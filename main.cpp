//引用头文件时，只能引用归档的头文件，即除了temp文件夹下的文件，具体看CMakeLists.txt
//abc
#include "view/drawMain.h"
#include "view/drewSetting.h"
#include <easyx.h>
#include <iostream>
int main() {
    //初始化窗口
    initgraph(width_window, length_window);


    //初始化两种消息
    ExMessage mouse;
    ExMessage Key;
    //初始化状态机
    statu condition;
    condition = statu::main;

    while (true) {
        switch (condition) {
            case statu::main: {
                drawMain();
                if (peekmessage(&mouse,EX_MOUSE)) {
                    if (mouse.message == WM_LBUTTONDOWN && button_setting.checkButton(mouse.x, mouse.y)) {
                        condition = statu::setting;
                    }
                    if (mouse.message == WM_LBUTTONDOWN && button_pause.checkButton(mouse.x, mouse.y)) {
                        condition = statu::main;
                    }
                }
                flushmessage();
                break;
            }
            case statu::setting: {
                drawSetting();
                if (peekmessage(&Key,EX_KEY)) {
                    if (Key.message == WM_KEYDOWN && Key.vkcode == VK_ESCAPE) {
                        condition = statu::main;
                        break;
                    }
                }
                if (peekmessage(&mouse,EX_MOUSE)) {
                    if (mouse.message == WM_LBUTTONDOWN && button_spectrum.checkButton(mouse.x,mouse.y)) {
                        condition = statu::setting;
                        system("start sources/cava/cava.exe");
                        std::cout<<"1"<<std::endl;
                    }
                }
                flushmessage();
                break;
            }
        }
    }
}
