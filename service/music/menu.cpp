/*
 *程序状态机
 */
#include "menu.h"
#include "../../function/def.h"
#include "../montior.h"

#include "../../function/button.h"

using std::cout;
using std::endl;



void menu::show_list() {
    cout << "show_list" << endl;
}

menu::menu() {
    condition = statu::main;
    while (1) {

        switch (condition) {
            case statu::main:
                break;
            case statu::setting:
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
