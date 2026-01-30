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
//播放/暂停音乐
void play_music (std::vector<Song> &songs_list,int *index,playStatu play_statu);

//播放下一曲/上一曲
void play_NextMusic(std::vector<Song> &songs_list,int *index,PlayMode play_mode);


//快进/快退
void play_music_argument(std::vector<Song> &songs_list,int index,int play_argument);

//快进/快退指数转换
int change_argument(std::vector<Song> &songs_list,int index,int x);
#endif