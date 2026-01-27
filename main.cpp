// main.cpp - 带音量控制
#include <graphics.h>
#include "ui.h"
#include "player.h"
#include <vector>
// 简单的全局播放列表
   std::vector<std::string> playlist = {
       "江南.mp3",
       "test.mp3"
   };
int currentSongIndex = 0;
int main() {


    // 1. 初始化图形窗口
    initgraph(500, 400);

    // 2. 创建播放器
    Player player;
    // 使用播放列表添加歌曲
    player.addToPlaylist("江南.mp3");
    player.addToPlaylist("test.mp3");
    // 3. 加载音乐文件
    if (!playlist.empty()) {
        player.load(playlist[currentSongIndex]);
        // 错误处理
    }

    // 4. 开始播放
    //player.play();

    // 5. 创建界面管理器
    PlayerUI ui(player);

    // 6. 主循环
    bool shouldExit = false;
    BeginBatchDraw();
    while (!shouldExit) {
        // 绘制界面
        ui.draw();


        FlushBatchDraw();
        // 控制刷新频率
        Sleep(10);
    }
    EndBatchDraw();
    // 7. 清理资源
    return 0;
}