/*
 * 音乐播放器主程序 (main.cpp)
 * 功能：
 * 1. 完整加载所有 UI 资源。
 * 2. 实现核心交互逻辑：
 * - 播放/暂停 (互斥切换)
 * - 静音/开音 (互斥切换)
 * - 播放模式 (单曲 -> 列表 -> 随机 轮换)
 * 3. 统一管理事件循环与绘图。
 */

#include <graphics.h>
#include <vector>
#include <string>
#include <iostream>
#include "button1.h" // 确保包含您的 button 头文件

// =================================================================================
// 全局配置区
// =================================================================================
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 800;

// ⚠️ 资源路径配置
// 主人，路径已经按照您的指示修正啦！
const std::string PATH_CONTROL = "image/control/";
const std::string PATH_MODE    = "image/audio_modes/";
const std::string PATH_UI      = "image/files_ui/";

int main() {
    // 1. 初始化窗口
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    setbkcolor(WHITE);
    cleardevice();

    // 2. 加载背景
    IMAGE img_bk;
    // 尝试加载背景，若失败则保留白底
    loadimage(&img_bk, "image/bk.png", WIN_WIDTH, WIN_HEIGHT, true);

    // 3. 按钮容器 (用于统一 Update 和 Draw)
    std::vector<button1*> buttons;

    // =================================================================================
    // 按钮创建与布局
    // =================================================================================

    // 布局基准点
    int centerX = WIN_WIDTH / 2;
    int bottomY = 650;  // 底部控制栏高度

    // 顶部布局参数 (Top Area)
    int topY    = 40;   // 顶部组件的起始 Y 坐标
    int rightMargin = 40; // 右侧边距
    int leftMargin  = 40; // 左侧边距

    // --- 尺寸定义 ---
    // 底部圆形按钮 (1:1)
    int sizeBig   = 80; // 播放/暂停
    int sizeMid   = 64; // 切歌
    int sizeSmall = 48; // 模式/音量
    int sizeIcon  = 48; // 设置按钮 (保持与其他功能键类似大小)

    // 顶部特殊形状按钮 (按原图比例 0.25 缩放)
    // Add File: 585*199 -> 146*50
    int wFile = 146, hFile = 50;
    // Add Folder: 445*199 -> 111*50
    int wFolder = 111, hFolder = 50;
    // Search: 1200*160 -> 300*40
    int wSearch = 300, hSearch = 40;

    int gapMid   = 20;
    int gapSmall = 15;

    // -------------------------------------------------------------------------
    // A. 播放控制组 (Play/Pause Group)
    // -------------------------------------------------------------------------

    // 我们需要单独保存这两个指针，以便在后面控制它们的显隐
    button_img* btn_play = nullptr;
    button_img* btn_pause = nullptr;

    int playX = centerX - sizeBig / 2;
    int playY = bottomY - sizeBig / 2;

    // 创建播放按钮 (初始状态：显示)
    btn_play = new button_img(playX, playY, sizeBig, sizeBig,
        PATH_CONTROL + "btn_play_norm.png",
        PATH_CONTROL + "btn_play_hover.png",
        PATH_CONTROL + "btn_play_down.png",
        PATH_CONTROL + "btn_play_mask.png");

    // 创建暂停按钮 (初始状态：隐藏，坐标与播放按钮完全重叠)
    btn_pause = new button_img(playX, playY, sizeBig, sizeBig,
        PATH_CONTROL + "btn_pause_norm.png",
        PATH_CONTROL + "btn_pause_hover.png",
        PATH_CONTROL + "btn_pause_down.png",
        PATH_CONTROL + "btn_pause_mask.png");
    btn_pause->setVisible(false); // <--- 关键：先藏起来

    // 加入总容器
    buttons.push_back(btn_play);
    buttons.push_back(btn_pause);

    // -------------------------------------------------------------------------
    // B. 其他控制按钮 (Prev, Next, Fwd, Bwd)
    // -------------------------------------------------------------------------

    // 快退
    buttons.push_back(new button_img(
        centerX - sizeBig/2 - gapMid - sizeMid, bottomY - sizeMid/2, sizeMid, sizeMid,
        PATH_CONTROL + "btn_backward_norm.png", PATH_CONTROL + "btn_backward_hover.png",
        PATH_CONTROL + "btn_backward_down.png", PATH_CONTROL + "btn_backward_mask.png"));

    // 上一曲
    buttons.push_back(new button_img(
        centerX - sizeBig/2 - gapMid - sizeMid - gapMid - sizeMid, bottomY - sizeMid/2, sizeMid, sizeMid,
        PATH_CONTROL + "btn_prev_norm.png", PATH_CONTROL + "btn_prev_hover.png",
        PATH_CONTROL + "btn_prev_down.png", PATH_CONTROL + "btn_prev_mask.png"));

    // 快进
    buttons.push_back(new button_img(
        centerX + sizeBig/2 + gapMid, bottomY - sizeMid/2, sizeMid, sizeMid,
        PATH_CONTROL + "btn_forward_norm.png", PATH_CONTROL + "btn_forward_hover.png",
        PATH_CONTROL + "btn_forward_down.png", PATH_CONTROL + "btn_forward_mask.png"));

    // 下一曲
    buttons.push_back(new button_img(
        centerX + sizeBig/2 + gapMid + sizeMid + gapMid, bottomY - sizeMid/2, sizeMid, sizeMid,
        PATH_CONTROL + "btn_next_norm.png", PATH_CONTROL + "btn_next_hover.png",
        PATH_CONTROL + "btn_next_down.png", PATH_CONTROL + "btn_next_mask.png"));

    // -------------------------------------------------------------------------
    // C. 播放模式组 (Mode Group) - 三态轮换
    // -------------------------------------------------------------------------
    button_img* btn_loop_all = nullptr;
    button_img* btn_loop_one = nullptr;
    button_img* btn_shuffle  = nullptr;

    int modeX = 150;
    int modeY = bottomY - sizeSmall / 2;

    // 列表循环 (初始显示)
    btn_loop_all = new button_img(modeX, modeY, sizeSmall, sizeSmall,
        PATH_MODE + "btn_loop_all_norm.png", PATH_MODE + "btn_loop_all_hover.png",
        PATH_MODE + "btn_loop_all_down.png", PATH_MODE + "btn_loop_all_mask.png");

    // 单曲循环 (初始隐藏)
    btn_loop_one = new button_img(modeX, modeY, sizeSmall, sizeSmall,
        PATH_MODE + "btn_loop_one_norm.png", PATH_MODE + "btn_loop_one_hover.png",
        PATH_MODE + "btn_loop_one_down.png", PATH_MODE + "btn_loop_one_mask.png");
    btn_loop_one->setVisible(false);

    // 随机播放 (初始隐藏)
    btn_shuffle = new button_img(modeX, modeY, sizeSmall, sizeSmall,
        PATH_MODE + "btn_shuffle_norm.png", PATH_MODE + "btn_shuffle_hover.png",
        PATH_MODE + "btn_shuffle_down.png", PATH_MODE + "btn_shuffle_mask.png");
    btn_shuffle->setVisible(false);

    buttons.push_back(btn_loop_all);
    buttons.push_back(btn_loop_one);
    buttons.push_back(btn_shuffle);

    // -------------------------------------------------------------------------
    // D. 音量控制组 (Volume Group) - 互斥切换
    // -------------------------------------------------------------------------
    button_img* btn_volume_on = nullptr;
    button_img* btn_mute      = nullptr;

    int volX = WIN_WIDTH - 250;
    int volY = bottomY - sizeSmall / 2;

    // 音量开 (初始显示)
    btn_volume_on = new button_img(volX, volY, sizeSmall, sizeSmall,
        PATH_MODE + "btn_volume_on_norm.png", PATH_MODE + "btn_volume_on_hover.png",
        PATH_MODE + "btn_volume_on_down.png", PATH_MODE + "btn_volume_on_mask.png");

    // 静音 (初始隐藏)
    btn_mute = new button_img(volX, volY, sizeSmall, sizeSmall,
        PATH_MODE + "btn_mute_norm.png", PATH_MODE + "btn_mute_hover.png",
        PATH_MODE + "btn_mute_down.png", PATH_MODE + "btn_mute_mask.png");
    btn_mute->setVisible(false);

    buttons.push_back(btn_volume_on);
    buttons.push_back(btn_mute);

    // -------------------------------------------------------------------------
    // E. 顶部 UI 组 (File & Settings)
    // -------------------------------------------------------------------------

    // 1. 设置 (Settings) - 放在左上角
    buttons.push_back(new button_img(
        leftMargin, topY,
        sizeIcon, sizeIcon,
        PATH_UI + "btn_settings_norm.png",
        PATH_UI + "btn_settings_hover.png",
        PATH_UI + "btn_settings_down.png",
        PATH_UI + "btn_settings_mask.png" // 已经修正为 mask
    ));

    // 2. 文件操作按钮 (右上角 第一排)
    // 布局：[添加目录] [添加文件] (靠右排列)

    // 添加文件 (最右侧)
    int fileX = WIN_WIDTH - rightMargin - wFile;
    buttons.push_back(new button_img(
        fileX, topY,
        hFile, wFile, // 注意：button构造函数参数是 (x, y, h, w) -> (x, y, length, width)
        PATH_UI + "btn_add_file_norm.png",
        PATH_UI + "btn_add_file_hover.png",
        PATH_UI + "btn_add_file_down.png",
        PATH_UI + "btn_add_file_mask.png"
    ));

    // 添加目录 (在添加文件的左边)
    int folderX = fileX - gapSmall - wFolder;
    buttons.push_back(new button_img(
        folderX, topY,
        hFolder, wFolder, // 高度, 宽度
        PATH_UI + "btn_add_folder_norm.png",
        PATH_UI + "btn_add_folder_hover.png",
        PATH_UI + "btn_add_folder_down.png",
        PATH_UI + "btn_add_folder_mask.png"
    ));

    // 3. 搜索框 (右上角 第二排 - 位于上方两个按钮下面)
    // 靠右对齐
    int searchX = WIN_WIDTH - rightMargin - wSearch;
    int searchY = topY + hFile + gapSmall; // 第一排高度 + 间距

    // 搜索 (Mask传空字符串)
    // 注意文件名修正为 btn_search_...
    buttons.push_back(new button_img(
        searchX, searchY,
        hSearch, wSearch, // 高度, 宽度
        PATH_UI + "btn_search_norm.png",
        PATH_UI + "btn_search_hover.png",
        PATH_UI + "btn_search_hover.png", // Down态复用Hover
        "" // 无掩码图
    ));


    // =================================================================================
    // 主消息循环
    // =================================================================================
    BeginBatchDraw();

    bool running = true;
    while (running) {
        ExMessage msg;
        while (peekmessage(&msg)) {
            // 处理鼠标逻辑
            if (msg.message == WM_LBUTTONUP) {
                // 只有在鼠标抬起时才触发逻辑切换，体验最好
                int mx = msg.x;
                int my = msg.y;

                // --- 1. 播放/暂停 切换 ---
                // checkButton 内部会自动检查 visible 属性
                // 如果 btn_play 不可见，checkButton 会直接返回 false
                if (btn_play->checkButton(mx, my)) {
                    // 点了播放 -> 切换到暂停状态
                    btn_play->setVisible(false);
                    btn_pause->setVisible(true);
                    std::cout << "State: Playing..." << std::endl;
                }
                else if (btn_pause->checkButton(mx, my)) {
                    // 点了暂停 -> 切换到播放状态
                    btn_pause->setVisible(false);
                    btn_play->setVisible(true);
                    std::cout << "State: Paused." << std::endl;
                }

                // --- 2. 音量/静音 切换 ---
                if (btn_volume_on->checkButton(mx, my)) {
                    btn_volume_on->setVisible(false);
                    btn_mute->setVisible(true);
                    std::cout << "State: Muted." << std::endl;
                }
                else if (btn_mute->checkButton(mx, my)) {
                    btn_mute->setVisible(false);
                    btn_volume_on->setVisible(true);
                    std::cout << "State: Volume On." << std::endl;
                }

                // --- 3. 播放模式 轮换 (One -> All -> Shuffle -> One) ---
                if (btn_loop_one->checkButton(mx, my)) {
                    btn_loop_one->setVisible(false);
                    btn_loop_all->setVisible(true);
                    std::cout << "Mode: Loop One" << std::endl;
                }
                else if (btn_loop_all->checkButton(mx, my)) {
                    btn_loop_all->setVisible(false);
                    btn_shuffle->setVisible(true);
                    std::cout << "Mode: Shuffle" << std::endl;
                }
                else if (btn_shuffle->checkButton(mx, my)) {
                    btn_shuffle->setVisible(false);
                    btn_loop_one->setVisible(true);
                    std::cout << "Mode: Loop All" << std::endl;
                }
            }
        }

        // 获取鼠标实时位置用于 Hover 效果
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(GetHWnd(), &p);
        bool isMouseDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

        // --- Update 状态 ---
        for (auto btn : buttons) {
            // updateState 内部也检查了 is_visible，所以不可见的按钮不会有 Hover 反应
            btn->updateState(p.x, p.y, isMouseDown);
        }

        // --- Render 绘制 ---
        cleardevice();

        // 1. 背景
        putimage(0, 0, &img_bk);

        // 2. 按钮
        for (auto btn : buttons) {
            // drawButton 内部检查了 is_visible
            btn->drawButton();
        }

        // 3. 调试文字 (提示当前状态)
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        // outtextxy(10, 10, "Debug: UI Logic Running...");

        FlushBatchDraw();
        Sleep(10);
    }

    EndBatchDraw();
    closegraph();

    // 内存清理
    for (auto btn : buttons) delete btn;

    return 0;
}