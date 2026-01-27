// playlist.h - 最简单播放列表
#pragma once
#include <vector>
#include <string>

class Playlist {
private:
    std::vector<std::string> songs;  // 歌曲列表
    int currentIndex = -1;           // 当前播放索引

public:
    // 添加歌曲
    void add(const std::string& filePath);

    // 获取信息
    int size() const;
    int getCurrentIndex() const;
    std::string getCurrent() const;

    // 导航
    void next();
    void previous();
    void setCurrent(int index);
};