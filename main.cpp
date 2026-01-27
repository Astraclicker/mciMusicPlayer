//引用头文件时，只能引用归档的头文件，即除了temp文件夹下的文件，具体看CMakeLists.txt
//test
#include "service/button.h"
#include <easyx.h>
int main() {
    //初始化窗口
    initgraph(width_window,length_window);

    //构建一个功能基础按钮
    button base_function (60,60,WHITE,button_style::roundrect);
    button base_spectrum (50,600,0xb79724,button_style::roundrect);
    //构建文本类
    txt CN(0,0,0xfcf7f1,"黑体");

    //初始化按钮
    button_img button_setting(30,30,base_function,"sources/image/files_ui/btn_settings_down.png");
    button_img button_pause(490,650,base_function,"sources/image/control/btn_pause_down.png");
    button_txt button_spectrum(300,300,"是否开启频谱",base_spectrum,CN);

    //初始化两种消息
    ExMessage mouse;
    ExMessage Key;

    //初始化状态机
    statu condition;
    condition = statu::main;

    while (true) {
        switch (condition) {
            case statu::main: {
                BeginBatchDraw();
                loadimage(NULL,bk_img.c_str());
                button_setting.drawButton();
                button_pause.drawButton();
                FlushBatchDraw();
                EndBatchDraw();
                if (peekmessage(&mouse,EX_MOUSE)) {
                    if (mouse.message == WM_LBUTTONDOWN && button_setting.checkButton(mouse.x,mouse.y)) {
                        condition = statu::setting;
                    }
                    if (mouse.message == WM_LBUTTONDOWN && button_pause.checkButton(mouse.x,mouse.y)) {
                        condition = statu::main;
                    }
                }
                break;
            }
            case statu::setting: {
                setfillcolor(0x808080);
                fillroundrect(width_window/8,length_window/8,width_window-width_window/8,length_window-length_window/8,10,10);
                if (peekmessage(&Key,EX_KEY)) {
                    if (Key.message == WM_KEYDOWN && Key.vkcode == VK_ESCAPE) {
                        condition = statu::main;
                        break;
                    }
                }
            }
        }
    }
}