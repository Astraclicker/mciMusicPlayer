/*
 * 检测功能实现
 * 实现检测用户是否进行相应操作
 */

#include "../view/menu/menu.h"

using  namespace std ;

bool monitor::monitor_addlist() {
    cout<<"monitor_addlist"<<endl;
    return true;
}//添加文件
bool monitor::monitor_add_he_list() {//判断是否添加合集
    cout<<"monitor_add_he_list"<<endl;
    return true;
}

bool monitor::monitor_list() {
    cout<<"monitor_list"<<endl;
    return true;
}//是否操作播放列表

bool monitor::monitor_start() {
    cout<<"monitor_start"<<endl;
    return true;
}//监测是否进行播放操作

bool monitor::monitor_comments() {
    cout<<"monitor_comments"<<endl;
       return true;
}//是否进行输入弹幕操作

bool monitor::monitor_log() {
    cout<<"monitor_log"<<endl;
    return true;
}//是否进行设置操作

bool monitor::monitor_list_end() {
    cout<<"monitor_list_end"<<endl;
    return true;
}
/*
 *监测改变音乐的播放方式
 */
bool monitor::change_list() {
cout<<"change_list"<<endl;
    return true;
}
bool monitor::monitor_end() {
    if (getchar() == '\n') {
        exit(0);
    }
    return false;
}//是否退出程序





void comment::sever_comments() {// 实现弹幕的读入功能
    cout<<11<<endl;
}

void comment::show_comments() {}//  实现弹幕的输出功能


