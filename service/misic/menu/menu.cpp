//
// Created by 神秘服务 on 2026/1/26.
//
#include "menu.h"
#include "../../function/def.h"


#include ".../monitor.h"

using namespace std;
void menu::show_menu() {
    initgraph(width_window, length_window);

        cout<<"show_menu"<<endl;

}
void menu::show_list() {
    cout<<"show_list"<<endl;
}

menu::menu() {
    //  {//监测是否载入设置
    //   ;//实现载入设置
    // }
    log l;
    this->show_menu();//展示主菜单

while (1) {


    monitor jc;
    if (MouseHit()){//鼠标监测 2为对应鼠标区域与操作判断
        if (2)jc.one_add(); //单击//添加文件

        if(2) //最下方按钮组判断区域//点击播放方式按钮组

        if (2) jc.ont_log();//进行设置

        if (2) jc.one_start();// 点击播放按钮

        if (2) jc.one_list();   //添加目录

        if (2)jc.monitor_list();//对音乐进行操作(双击)

        if (2)jc.one_end(); //监测退出

        if (2)jc.one_list();//切换合集 单击改变播放列表的显示(读入数据？) 、//有问题
    }
    if (jc.monitor_list_end()) {//歌曲播放结束
        //根据播放模式 选择文件
        ;//播放文件
        getchar();
    }

    //monitor();
}
}

/*
 * 实现监测操作及跳转
 *  根据用户点击的返回值决定调用哪个部分
 */
monitor::monitor() {
   cout<<"monitor"<<endl;
}




/*
 * 实现歌曲播放的流程
 */
