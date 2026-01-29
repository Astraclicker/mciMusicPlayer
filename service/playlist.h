// playlist.h - 最简单播放列表
#pragma once                    // 防止头文件被重复包含
#include <vector>               // 引入vector容器，用于存储歌曲列表
#include <string>               // 引入string类，用于处理文件路径字符串

class Playlist {                // 播放列表类定义
private:
    std::vector<std::string> songs;  // 歌曲列表：存储所有歌曲的文件路径
    int currentIndex = -1;           // 当前播放索引：-1表示列表为空，无当前歌曲

public:                         // 公有成员函数，对外提供接口
    // 添加歌曲：将文件路径添加到播放列表中，如果列表为空则设置当前索引为0
    void add(const std::string& filePath);

    // 获取信息：返回播放列表中歌曲的总数
    int size() const;
    // 获取信息：返回当前正在播放歌曲的索引
    int getCurrentIndex() const;
    // 获取信息：返回当前正在播放歌曲的文件路径，如果无当前歌曲则返回空字符串
    std::string getCurrent() const;

    // 导航：切换到播放列表中的下一首歌曲，到达末尾时循环到第一首
    void next();
    // 导航：切换到播放列表中的上一首歌曲，到达开头时循环到最后一首
    void previous();
    // 导航：设置当前播放的歌曲索引，如果索引有效则更新当前索引
    void setCurrent(int index);
};