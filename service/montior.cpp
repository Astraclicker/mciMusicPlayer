/*
 * 检测功能实现
 * 实现检测用户是否进行相应操作
 */

#include "montior.h"

using  namespace std ;

bool monitor::mouse() {
    cout<<"mouse"<<endl;
    return true;
}

bool monitor::key() {
    cout<<"key"<<endl;
    return true;
}

void monitor::one_add() {
    cout<<"monitor_addlist"<<endl;

}//添加文件
void monitor::one_add_he_list() {//判断是否添加合集
    cout<<"monitor_add_he_list"<<endl;

}

void monitor::monitor_list() {
    cout<<"monitor_list"<<endl;

}//操作播放列表(//双击操作)

void monitor::one_start() {
    cout<<"monitor_start"<<endl;

}//点击了播放按钮 切换状态

void monitor::monitor_comments() {
    cout<<"monitor_comments"<<endl;

}//输入弹幕操作

void monitor::ont_log() {
    cout<<"monitor_log"<<endl;

}//设置操作

bool monitor::monitor_list_end() {
    cout<<"monitor_list_end"<<endl;
    return true;
}//检测歌曲是否结束
/*
 *监测改变音乐的播放方式
 */
void monitor::one_list() {
cout<<"change_list"<<endl;

}
void monitor::one_end() {
    if (getchar() == '0') {
        exit(0);
    }

}//是否退出程序





// void comment::sever_comments() {// 实现弹幕的读入功能
//     cout<<11<<endl;
// }
//
// void comment::show_comments() {}//  实现弹幕的输出功能


