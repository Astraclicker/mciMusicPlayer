#pragma once
#include <graphics.h>
#include <iostream>
#include MusicManger.h
using namespace std;

//播放器的ui界面
//主界面
//设置界面等
class UI {
private:
    IMAGE backgroundimg;//主界面背景图
    IMAGE setimg;//设置背景图
    IMAGE coverimg;//专辑封面
    //.....


public:
    UI();
    //加载图片
    void InitResource();
    //绘制主界面
    //从MusicManager里获取信息
    void DrawMainScreen(MusicManger &manager);
    //绘制设置界面
    void DrawSetSreen();
};