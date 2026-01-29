/*
 *程序状态机
 */
#include "menu.h"
#include "../../function/def.h"
#include "../montior.h"

#include "../../function/button.h"
#include "../../view/drawMain.h"
#include "../../view/drewSetting.h"

using std::cout;
using std::endl;



void menu::show_list() {
    cout << "show_list" << endl;
}

menu::menu() {
    initgraph(width_window,length_window);
    condition = statu::main;
    ExMessage mouse;
    while (1) {

        switch (condition) {
            case statu::main:
                drawMain();
                getmessage(&mouse,EX_MOUSE);
                if (mouse.message==WM_LBUTTONDOWN&&button_setting.checkButton(mouse.x,mouse.y)) {
                    condition = statu::setting;
                }
                break;
            case statu::setting:
                drawSetting();
                break;
        }

    }
}

/*
 * 实现监测操作及跳转
 *  根据用户点击的返回值决定调用哪个部分
 */
monitor::monitor() {
    cout << "monitor" << endl;
}


/*
 * 实现歌曲播放的流程
 */
