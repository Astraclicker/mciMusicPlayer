#include "playMusic.h"
#include <windows.h>
#include "../view/drawPlayList.h"
#include "../view/drewSetting.h"
//暂停/播放控件
void control_music (playStatu&status) {
    if (status == playStatu::pause) {
        // 暂停 -> 播放
        mciSendString("play myaudio", NULL, 0, NULL);
        status = playStatu::play;
    }
    else { // status == PlayStatus::play
        // 播放 -> 暂停
        mciSendString("stop myaudio", NULL, 0, NULL);
        status = playStatu::pause;
    }
}

void play_music (int newindex) {
    if (newindex < 0 || newindex >= my_play_list_controller.get_current_playlist_size()) return;
    current_song_index = newindex;
    // 停止当前播放
    mciSendString("close myaudio", NULL, 0, NULL);

    // 打开新歌曲
    std::string cmd = "open \"" + my_play_list_controller.get_current_song_path(current_song_index) + "\" alias myaudio";
    mciSendString(cmd.c_str(), NULL, 0, NULL);

    // 播放
    mciSendString("play myaudio", NULL, 0, NULL);
    play_statu = playStatu::play;
    setVolume(volume);
}

//播放下一曲/上一曲
void play_NextMusic() {
    switch (play_mode) {
        case PlayMode::Sequence:
            current_song_index = current_song_index + 1;
            if (current_song_index >= my_play_list_controller.get_current_playlist_size()) {
                current_song_index = 0;  // 循环到第一首
            }
            break;
        case PlayMode::Sing_Loop:
            //index=index不变
            break;
        case PlayMode::Random:
            current_song_index=rand() % my_play_list_controller.get_current_playlist_size() ;
            break;
    }
    play_music(current_song_index);
}

void play_PreviousMusic() {
    switch (play_mode) {
        case PlayMode::Sequence:
            current_song_index=current_song_index - 1;
            if (current_song_index < 0) {
                current_song_index = my_play_list_controller.get_current_playlist_size() - 1;  // 循环到最后一首
            }
            break;
        case PlayMode::Sing_Loop:
            //index=index不变
            break;
        case PlayMode::Random:
            current_song_index=rand() % my_play_list_controller.get_current_playlist_size() ;
            break;
    }
    play_music(current_song_index);
}

//播放结束判断，下一首自动播放
void checkAndPlayNext() {
    static bool wasPlaying = false;
    char status[256];

    mciSendString("status myaudio mode", status, sizeof(status), NULL);

    if (strcmp(status, "playing") == 0) {
        wasPlaying = true;
    }
    else if (strcmp(status, "stopped") == 0 && wasPlaying) {
        wasPlaying = false;
        play_NextMusic();
    }
}
//快进/快退
void fastForward(int milliseconds) {
    char cmd[256];
    char positionStr[64];

    // 1. 获取当前位置
    mciSendString("status myaudio position", positionStr, sizeof(positionStr), 0);
    long currentPos = atol(positionStr);

    // 2. 获取媒体总长度（防止超出范围）
    long totalLength = my_play_list_controller.get_current_song_time();

    // 3. 计算新位置
    long newPos = currentPos + milliseconds;
    if (newPos > totalLength) {
        newPos = totalLength; // 不超过总长度
    }

    // 4. 跳转到新位置
    sprintf(cmd, "seek myaudio to %ld", newPos);
    mciSendString(cmd, NULL, 0, NULL);

    // 5. 继续播放
    mciSendString("play myaudio", NULL, 0, NULL);
}
void fastBackward(int milliseconds) {
    char cmd[256];
    char positionStr[64];

    // 1. 获取当前位置
    mciSendString("status myaudio position", positionStr, sizeof(positionStr), 0);
    long currentPos = atol(positionStr);

    // 2. 计算新位置（不小于0）
    long newPos = currentPos - milliseconds;
    if (newPos < 0) {
        newPos = 0;
    }

    // 3. 跳转到新位置
    sprintf(cmd, "seek myaudio to %ld", newPos);
    mciSendString(cmd, NULL, 0, NULL);

    // 4. 继续播放
    mciSendString("play myaudio", NULL, 0, NULL);
}

//简易进度条
float getProgress() {
    char posStr[64];

    // 获取当前位置
    mciSendString("status myaudio position", posStr, sizeof(posStr), 0);
    long currentPos = atol(posStr);

    // 获取总长度
    long totalLen = my_play_list_controller.get_current_song_time();

    // 计算进度
    if (totalLen > 0) {
        return (float)currentPos / totalLen;
    }
    return 0.0f;
}
void drawSimpleProgressBar(int x, int y, int width, int height, float progress) {
    // 1. 绘制背景（灰色）
    setfillcolor(LIGHTGRAY);
    fillrectangle(x, y, x + width, y + height);

    // 2. 绘制进度（蓝色）
    if (progress > 0) {
        int progressWidth = (int)(width * progress);
        setfillcolor(RGB(38, 120, 255));
        fillrectangle(x, y, x + progressWidth, y + height);
    }

    // 3. 绘制边框
    rectangle(x, y, x + width, y + height);
    // 4. 绘制拖拽小圆圈
    if (progress > 0) {
        int circleX = x + (int)(width * progress);
        int circleY = y + height / 2;
        int circleRadius = 12;  // 固定大小

        // 外圈（深色边框）
        setlinecolor(RGB(20, 70, 180));
        setfillcolor(WHITE);
        fillellipse(circleX - circleRadius, circleY - circleRadius,
                   circleX + circleRadius, circleY + circleRadius);
        setlinecolor(WHITE);
    }
}

void clickProgressBarToSeek(int mouseX) {
    // 1. 计算点击位置对应的进度 (0.0 ~ 1.0)
    float progress = (float)mouseX / 1280.0f;
    if (progress < 0) progress = 0;
    if (progress > 1) progress = 1;

    // 2. 获取音频总长度
    long totalTime = my_play_list_controller.get_current_song_time();

    // 3. 计算目标时间
    long targetTime = (long)(totalTime * progress);

    // 4. 直接跳转（一句话搞定）
    char cmd[128];
    sprintf(cmd, "seek myaudio to %ld", targetTime);
    mciSendString(cmd, NULL, 0, NULL);

    // 5. 继续播放
    mciSendString("play myaudio", NULL, 0, NULL);
    play_statu=playStatu::play;
}

