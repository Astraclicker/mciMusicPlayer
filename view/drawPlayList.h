/*
 *功能：
 *在主界面打印vector数组内的音乐名称到主界面左边
 *负责人：
 *现实的延续
 */
#ifndef MCIMUSICPLAYER_DRAWPLAYLIST_H
#define MCIMUSICPLAYER_DRAWPLAYLIST_H
#include "../service/Song.h"
#include <vector>

void draw_play_list(std::vector<Song> &songs_list);
#endif