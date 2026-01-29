#pragma once

#include <iostream>
#include <vector>

class menu{//实现主菜单的显示

protected:

public:
    menu();
    void show_list();//根据数据展示播放列表
};


class comment{//弹幕实现对象
public:
   void sever_comments();//实现弹幕的读入 存贮
   void show_comments();//实现弹幕的输出
};