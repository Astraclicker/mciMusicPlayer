// ui.cpp
#include "ui_liangyu.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <vector>
// 全局播放列表变量（简单实现）
extern std::vector<std::string> playlist;
extern int currentSongIndex;


PlayerUI::PlayerUI(Player& p) : player(p) {
    // 初始化滑块位置
    sliderX = 150 + (player.getVolume() * 2);
}

void PlayerUI::draw() {
    cleardevice();
    setbkcolor(WHITE);
    handleMouse();
    handleKeyboard();
    drawTitle();
    drawStatus();
    drawPlaylists();
    drawVolumeControl();
    drawHelp();
}

void PlayerUI::drawTitle() {
    settextcolor(BLACK);
    outtextxy(200, 30, ("音乐播放器"));
}

void PlayerUI::drawPlaylists() {
    settextcolor(BLACK);

    // 播放列表标题
    outtextxy(50, 150, "播放列表:");

    // 绘制每首歌曲
    for (int i = 0; i < playlist.size(); i++) {
        int y = 180 + i * 25;  // 每项间隔25像素

        // 当前播放的歌曲高亮显示
        if (i == currentSongIndex) {
            setfillcolor(RGB(220, 230, 255));  // 浅蓝色背景
            fillrectangle(50, y, 300, y + 23);
        }

        // 歌曲名称
        char itemText[100];
        sprintf(itemText, "%d. %s", i + 1, playlist[i].c_str());
        outtextxy(55, y + 5, itemText);

        // 边框
        rectangle(50, y, 300, y + 23);
    }
}

void PlayerUI::drawStatus() {
    // 显示文件
    // 显示当前歌曲
    if (!playlist.empty() && currentSongIndex < playlist.size()) {
        char songInfo[100];
        sprintf(songInfo, "正在播放: %s", playlist[currentSongIndex].c_str());
        outtextxy(100, 80, songInfo);
    } else {
        outtextxy(100, 80, "未加载歌曲");
    }

    // 显示播放状态
    if (player.playing()) {
        outtextxy(150, 110, "状态: 播放中");
    } else {
        outtextxy(150, 110, "状态: 已暂停");
    }
}



void PlayerUI::drawVolumeControl() {
    outtextxy(50, 240, "音量调节:");

    // 绘制音量滑块轨道
    rectangle(150, 240, 350, 260);

    // 绘制填充部分（蓝色）
    setfillcolor(BLUE);
    fillrectangle(150, 240, sliderX, 260);

    // 绘制滑块
    setfillcolor(RED);
    fillrectangle(sliderX - 5, 235, sliderX + 5, 265);

    // 显示音量数值
    char volText[20];
    sprintf(volText, "%d%%", player.getVolume());
    outtextxy(360, 240, volText);

    // 显示提示
    outtextxy(150, 280, "拖动滑块调节音量");
}

void PlayerUI::drawHelp() {
    outtextxy(50, 280, "控制按键:");
    outtextxy(50, 300, "空格:播放/暂停  S:停止");
    outtextxy(50, 320, "N:下一首  P:上一首");
    outtextxy(50, 340, "ESC:退出程序");
    outtextxy(50, 360, "点击歌曲切换");
}

void PlayerUI::handleMouse() {
    if (MouseHit()) {
        MOUSEMSG msg = GetMouseMsg();

        if (msg.uMsg == WM_LBUTTONDOWN) {
            // 检查是否点击了播放列表项
            if (msg.x >= 50 && msg.x <= 300) {
                for (int i = 0; i < playlist.size(); i++) {
                    int y = 180 + i * 25;
                    if (msg.y >= y && msg.y <= y + 23) {
                        // 点击了第i首歌
                        currentSongIndex = i;
                        player.close();
                        player.load(playlist[currentSongIndex]);
                        player.play();
                        break;
                    }
                }
            }
            // 检查是否点击了滑块区域
            if (msg.x >= 150 && msg.x <= 350 &&
                msg.y >= 235 && msg.y <= 265) {
                dragging = true;
                }
        }
        else if (msg.uMsg == WM_LBUTTONUP) {
            dragging = false;
        }
        else if (msg.uMsg == WM_MOUSEMOVE && dragging) {
            // 拖动滑块
            sliderX = msg.x;
            if (sliderX < 150) sliderX = 150;
            if (sliderX > 350) sliderX = 350;

            // 计算新音量
            int newVolume = (sliderX - 150) / 2;
            if (newVolume != player.getVolume()) {
                player.setVolume(newVolume);  // 设置新音量
            }
        }
    }
}

bool PlayerUI::handleKeyboard() {
    if (_kbhit()) {
        char ch = _getch();

        switch (ch) {
            case ' ':
                player.toggle();  // 空格键切换播放/暂停
                break;

            case 's':
            case 'S':
                player.stop();  // S键停止
                break;
            case 'n':  // N：下一首（新增）
            case 'N':
                if (!playlist.empty()) {
                    currentSongIndex = (currentSongIndex + 1) % playlist.size();
                    player.close();
                    player.load(playlist[currentSongIndex]);
                    player.play();
                }
                break;

            case 'p':  // P：上一首（新增）
            case 'P':
                if (!playlist.empty()) {
                    currentSongIndex = (currentSongIndex - 1 + playlist.size()) % playlist.size();
                    player.close();
                    player.load(playlist[currentSongIndex]);
                    player.play();
                }
                break;

            case 27:  // ESC键
                player.close();
                closegraph();
                break;
        }
    }
}

