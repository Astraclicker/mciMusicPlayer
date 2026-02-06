/*
 *功能：
 *根据传入的vector数组和编号播放音乐
 *负责人：
 *111
 */

#ifndef MCIMUSICPLAYER_PLAYMUSIC_H
#define MCIMUSICPLAYER_PLAYMUSIC_H
#include "../service/def.h"
#include <vector>
//暂停/播放控件

void control_music(playStatu &status);

void play_music(int newindex);

// //播放下一曲/上一曲
void play_NextMusic();

void play_PreviousMusic();

//播放结束判断，下一首自动播放
void checkAndPlayNext();

//快进/快退
void fastForward(int milliseconds = 10000);

void fastBackward(int milliseconds = 10000);

//简易进度条
float getProgress();

void drawSimpleProgressBar(int x, int y, int width, int height, float progress);

void clickProgressBarToSeek(int mouseX);

#endif
