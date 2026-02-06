#ifndef MCIMUSICPLAYER_DRAWLYRICS_H
#define MCIMUSICPLAYER_DRAWLYRICS_H
#include "../service/def.h"


//获取当前毫秒数
long long getCurrenTime();

//解析歌词
void loadLyrics();

//绘制歌词
void drawLyrics(int index);

//展示歌曲信息
void drawInformation();

#endif //MCIMUSICPLAYER_DRAWLYRICS_H
