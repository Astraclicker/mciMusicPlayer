/*
 *功能：
 *在主界面打印vector数组内的音乐名称到主界面左边
 *负责人：
 *现实的延续
 */
#ifndef MCIMUSICPLAYER_DRAWPLAYLIST_H
#define MCIMUSICPLAYER_DRAWPLAYLIST_H
#include "../service/Song.h"
#include <vector>
#include "../function/button.h"

class playlist {
public:
    // 默认构造函数，初始化播放列表背景，以及播放列表歌曲字体样式
    playlist();
    ~playlist();
    // 重新加载播放列表的中的歌曲按钮
    void reload(const std::vector<Song> &songs_list_data);
    // 更新播放列表歌曲按钮的状态
    // 传入鼠标滚轮移动消息，根据其值改变song_buttons中的各个按钮的y坐标
    void update_song_buttons(int wheel_move);
    // 绘制播放列表
    // 如果song_buttons中按钮的y坐标不在播放列表的区域内，不绘制
    void draw();
    // 检测是否点击到歌曲按钮
    // 如果点击到，则返回对应歌曲的索引
    // 如果没有，则返回-1
    // play_music函数拿到-1后应该直接return，不播放音乐
    int is_clisk_button(int x,int y);

private:
    // 播放列表背景
    button_color* playlist_button;
    // 歌曲按钮字体
    txt songFont;
    // 歌曲按钮容器
    std::vector<button_txt*> song_buttons;
};

// 初始化一个默认播放列表
inline playlist defalt_playlist;

#endif