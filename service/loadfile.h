/*
 *功能：
 *将songs_address地址下的所有音乐文件保存到vector数组中
 *包括音乐编号和音乐文件名
 *负责人：小林·牧之原稀音
 */
#ifndef MCIMUSICPLAYER_LOADFILE_H
#define MCIMUSICPLAYER_LOADFILE_H
#include "Song.h"
#include <string>
#include <vector>
#include "tinyfiledialogs.h"
std::string STRtoANSI(const std::string& str);
void load_file(std::string music_address,std::vector<Song> &songs_list);
void load_simple_file(std::vector<Song> &songs_list);
#endif