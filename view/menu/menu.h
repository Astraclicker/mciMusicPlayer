//
// Created by 神秘服务 on 2026/1/24.
//

#ifndef UNTITLED_1_H
#define UNTITLED_1_H
#include <iostream>
#include <vector>
class menu{//实现主菜单的显示
private:
    //展示播放列表?
public:
    menu();
    void show_menu();//展示主菜单界面
    void show_list();//根据数据展示播放列表
};

class comment{//弹幕实现对象
public:

   void sever_comments();//实现弹幕的读入 存贮
   void show_comments();//实现弹幕的输出
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