/*
 *负责人：小林
 *读取指定文件或文件夹下的音乐文件
 */
#ifndef MCIMUSICPLAYER_LOADFILE_H
#define MCIMUSICPLAYER_LOADFILE_H
#include "Song.h"
#include <string>
#include <vector>
#include "tinyfiledialogs.h"

//转码，utf-8转ANSI
std::string STRtoANSI(const std::string &str);

//读取文件夹
void load_file(std::string music_address, std::vector<Song> &songs_list);

//读取单独的文件
void load_simple_file(std::vector<Song> &songs_list);
#endif
