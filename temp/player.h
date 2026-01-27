// player.h
#pragma once
#include <string>
#include "playlist.h"
class Player {
private:
    bool isPlaying = false;//true:正在播放   false:暂停（关闭）
    std::string deviceName = "myMusic";
    int volume;
    // 添加播放列表成员
    Playlist playlist;
public:
    // 播放列表相关（新增）
    void addToPlaylist(const std::string& filePath);
    int playlistSize() const;
    std::string getCurrentSong() const;
    void playNext();
    void playPrevious();
    void playAt(int index);

    bool load(const std::string& filename);//根据文件路径加载.mp3文件
    void play();//播放当前音频
    void pause();//暂停
    void stop();//停止（终止本次播放，再次点击播放从头开始播放）
    void toggle();//切换
    bool playing() const;//获取播放状态
    void close();

    // 音量控制（新增）
    void setVolume(int percent);  // 设置音量 0-100
    int getVolume() const;        // 获取当前音量

};