/*
 *功能：
 *将songs_address地址下的所有音乐文件保存到vector数组中
 *包括音乐编号和音乐文件名
 *负责人：火豆
 */
#ifndef MCIMUSICPLAYER_LOADFILE_H
#define MCIMUSICPLAYER_LOADFILE_H
#include "Song.h"
#include <string>
#include <vector>
void load_file(std::string songs_address,std::vector<Song> &songs_list);
#endif