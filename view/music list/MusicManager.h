#pragma once
#include<vector>
#include "../../service/misic/Song.h"
#include "../../function/def.h"
using namespace std;
//管理歌单，播放模式，暂停



class MusicManager {
private:
    PlayMode Mode;//播放模式
    vector<Song> playlist;//装歌曲的动态列表  是不是差一个大小
    int index;//当前播放歌曲索引

public:
    MusicManager();
    //歌单管理
    void addSong();
    //获取当前歌曲信息
    Song* getCurrentSong();
    //播放控制
    void play();
    void pause();
    //切歌逻辑
    void next();
    void pre();
    //播放模式设置
    void SetMode();
};