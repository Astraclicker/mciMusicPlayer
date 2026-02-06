/*
 *一首歌曲的数据
 *包括编号和名称
 */

#ifndef MCIMUSICPLAYER_SONG_H
#define MCIMUSICPLAYER_SONG_H
#include <string>

class Song {
public:
    int song_index;
    std::string song_name;
    std::string song_root;
    std::string song_address;
    int song_time;
};
#endif //MCIMUSICPLAYER_SONG_H
