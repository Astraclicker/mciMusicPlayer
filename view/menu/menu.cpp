//
// Created by 神秘服务 on 2026/1/26.
//
#include "menu.h"


using namespace std;
void menu::show_menu() {


        cout<<"show_menu"<<endl;

}


menu::menu() {
    //  {//监测是否载入设置
    //   ;//实现载入设置
    // }
    log l;
    this->show_menu();//展示主菜单

while (1) {//检测用户操作 操作了进行判断


    monitor jc;
    if (jc.monitor_list_end()) {//歌曲播放结束
        //根据播放模式 选择文件
        ;//播放文件
    }

    //monitor();
}
}

/*
 * 实现监测操作及跳转
 *  根据用户点击的返回值决定调用哪个部分
 */
monitor::monitor() {
    if (1){//用户进行操作在进行判断？
    if (this->monitor_add_he_list()){}//添加文件
    if (this->monitor_addlist()){}//添加目录
    if (this->monitor_list()){}//是否对播放列表进行操作(双击 切换合集  )
    if (this->change_list()){}//点击播放方式
    if (this->monitor_comments()){}//是否输入弹幕
    if (this->monitor_log()){}//监测是否进行设置
    if (this->monitor_end()) {}//监测退出
    if (this->monitor_start()) {;}// 监测是否点击播放按钮
}
}




/*
 * 实现歌曲播放的流程
 */
