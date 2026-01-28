#include <easyx.h>
#include <iostream>
#include <fstream>
#include "huodou.h"

using namespace std;


//————————————————————————————————————————————逻辑属性——————————————————————————————————————
//这一部分是声明一些结构体，全局变量等内在的属性，方便做展示部分的时候直接调用
typedef struct {
    string title;//标题
    string artist;//歌手
    string  album;//专辑
    bool collection;//收藏
    float duration;//时长，秒
}Song;//歌曲信息

//歌词结构体
typedef struct {
    float duration; // 歌曲时长
    string text;    //歌词
}Songset;

//歌曲列表
typedef struct {
    Song* songs;
    int song_count; //歌曲数量
    int current_index;  //当前歌曲序号
} songlist;

// 播放/暂停控制
void CONTROLPAUSE() {
    isPlaying = !isPlaying;
}


// 设置背景颜色并初始化
void setBackground() {
    initgraph(800, 600);
    setbkcolor(RGB(25, 25, 35));
    cleardevice();
    settextstyle(20, 0, ("微软雅黑"));
    settextcolor(WHITE);
}

//读取配置文件（音量/皮肤/播放列表/上次播放进度)
void readSongsetting(){}
//读取文件中歌曲列表
void readSongList() {}

// 调节播放速度
void controlSpeed() {}

//播放模式调整
void controlplaystyle() {}

//——————————————————————————————————————————视觉层——————————————————————————————————————————————————
// 绘制主界面，需注意以下几点：绘制主页面、绘制图标、处理点击事件及反馈。这些功能可分开实现
/*
绘制主界面
1.清屏，绘制背景
2.绘制标题栏和各种控制窗口按钮
3.绘制底部状态栏
4.绘制播放列表
5.绘制专辑封面
6.绘制当前播放信息
*/
//清屏并绘制背景，标题栏，绘制底部状态栏
void drawMainPage() {

    initgraph(800,600);
    setbkcolor(BLUE);
    cleardevice();

    //尝试绘制一个按钮
    setfillcolor(GREEN);
    fillrectangle(50,70,50 + 30,70 + 60);

    settextcolor(YELLOW);
    settextstyle(20,0,"仿宋");
    outtextxy(60,75,"按钮");

}
// 绘制图标（如按钮、控制图标等）
void drawIcon() {}
//绘制专辑封面，播放信息
void drawPhoto(){}

// 处理主界面的鼠标点击事件，包括图标和按钮的交互反馈
void MainMousePeek() {
    ExMessage msg = {0};
    while (true) {
        if (peekmessage(&msg,EX_MOUSE)&&msg.x>= 50 && msg.x <= 110 && msg.y >= 70 && msg.y <= 100 && msg.message == WM_LBUTTONDOWN) {
                closegraph();
                cout << 3;

        }
    }
}

// 实现基础播放控制功能：播放/暂停、上一首/下一首、收藏、播放速度调节等
// 播放/暂停控制
void controlPlayPause() {}

// 上一首/下一首切换
void controlTrackChange() {}


// 收藏当前歌曲
void controlFavorite() {
    isCollect = !isCollect;
}

// 绘制播放页面（专用于播放时的界面）
void drawPlayPage() {}

// 绘制专辑图片（支持特定格式，如圆形裁剪）
void drawAlbumArt() {}

// 实现播放页面上半部分的功能切换（如歌词、专辑信息等）
void switchUpperSection() {}

// 输出可滚动的歌词显示
void displayLyrics() {}

// 处理播放页面下半部分的控制点击（直接调用控制函数）
void handlePlaybackControl() {}


int main() {
    void drawMainPage();
    void MainMousePeek();


    return 0;
}