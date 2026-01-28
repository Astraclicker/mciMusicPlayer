//
// Created by 神秘服务 on 2026/1/24.
//

#ifndef UNTITLED_1_H
#define UNTITLED_1_H
#include <iostream>
#include <vector>
class menu{//实现主菜单的显示
public:
    menu();
    void show_menu();//展示主菜单界面

};

class comment{//弹幕实现对象
public:

   void sever_comments();//实现弹幕的读入 存贮
   void show_comments();//实现弹幕的输出
};

class monitor{
private:
    bool monitor_addlist();//添加音乐监测
    bool monitor_add_he_list();//添加目录
    bool monitor_start();//是否正在进行播放
    bool monitor_list();//是否操作播放列表中的音乐(双击)
    bool change_list();//是否改变播放列表
    bool monitor_comments();//是否操作弹幕
    bool monitor_log();//是否操作设置
    bool monitor_end();//是否进行退出
    public:
    monitor();//监测用户操作
    bool monitor_list_end();//音乐是否播放停止

};



class log{
public:
      log();//实现加载设置
void show_log();//展示设置界面
void sever_log();//改变设置
void next_log();//顺序播放方式
void rad_log();//随机播放方式
};


#endif //UNTITLED_1_H