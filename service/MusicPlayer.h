#include <iostream>
#include "../temp/MusicManager.h"
#include "../temp/button.h"
#include "./misic/Song.h"
#include "../function//UI.h"

class MusicPlayer {
private:
    //创建各对象
    MusicManager manager;
    UI ui;
    Button playButton;
    Button nextButton;
    //....

    //绘制
    void DrawALL();//在打印主界面的时候同时调用
    //处理鼠标交互
    void Handinput();//检测播放列表的操作，有则调用该函数

public:
    MusicPlayer();
    void run();
};