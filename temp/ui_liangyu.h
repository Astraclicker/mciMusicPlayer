// ui.h - 界面绘制和事件处理
#pragma once
#include "player.h"

class PlayerUI {
private:
    Player& player;  // 引用播放器

    // UI状态
    int sliderX = 150;  // 音量滑块位置
    bool dragging = false;  // 是否正在拖动

public:
    PlayerUI(Player& p);

    // 绘制界面
    void draw();
private:
    // 绘制各部分
    void drawTitle();
    void drawStatus();
    void drawControls();
    void drawPlaylists();
    void drawVolumeControl();
    void drawHelp();

    // 处理鼠标事件
    void handleMouse();

    // 处理键盘事件
    bool handleKeyboard();
};