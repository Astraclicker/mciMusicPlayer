#include <iostream>
#include "MusicManager.h"
#include "Button.h"
#include "Song.h"
#include "UI.h"

class MusicPlayer {
private:
    //创建各对象
    MusicManager manager;
    UI ui;
    Button playButton;
    Button nextButton;
    //....

    //绘制
    void DrawALL();
    //处理鼠标交互
    void Handinput();

public:
    MusicPlayer();
    void run();
};