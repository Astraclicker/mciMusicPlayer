// playlist.cpp - 简单实现
#include "playlist.h"

void Playlist::add(const std::string& filePath) { // 添加歌曲到播放列表。如果列表为空，将当前索引设为0。
    this->songs.push_back(filePath);
    if (currentIndex == -1) {
        currentIndex = 0;
    }
}

int Playlist::size() const { // 返回播放列表中的歌曲数量。
    return songs.size();
}

int Playlist::getCurrentIndex() const { // 获取当前歌曲的索引。
    return currentIndex;
}

std::string Playlist::getCurrent() const { // 获取当前歌曲的文件路径。如果没有当前歌曲，返回空字符串。
    if (currentIndex >= 0 && currentIndex < songs.size()) {
        return songs[currentIndex];
    }
    return "";
}

void Playlist::next() {
    if (songs.empty()) return;
    currentIndex = (currentIndex + 1) % songs.size();
} // 切换到下一首歌曲，到达列表末尾时循环到第一首。

void Playlist::previous() {
    if (songs.empty()) return;
    currentIndex = (currentIndex - 1 + songs.size()) % songs.size();
} // 切换到上一首歌曲，到达列表开头时循环到最后一首。

void Playlist::setCurrent(int index) {
    if (index >= 0 && index < songs.size()) {
        currentIndex = index;
    }
} // 如果索引有效，设置当前歌曲的索引。