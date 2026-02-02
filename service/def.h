/*
*为程序提供宏
 *枚举
 */
#pragma once

#include <vector>
#include "Song.h"
//窗口大小
constexpr int width_window =1280;
constexpr int  length_window= 800;

//专辑封面大小
constexpr int width_album = 450;
constexpr int length_album= 450;

//音乐路径
inline std::string music_path = "sources/music";

//背景图片
inline std::string bk_img = "sources/image/bk.png";

//播放方式
enum class PlayMode {Sequence,Sing_Loop,Random};

//按钮形状
enum class button_style {
    ellipse,
    roundrect
};

//主界面状态
enum class statu {
    main,
    setting
};

//当前播放状态
enum  class playStatu {
    play,
    pause
};
//声明状态机
inline statu condition;
inline playStatu play_statu;
inline PlayMode play_mode;

//播放列表
inline std::vector<Song>songs_list;
//开始的编号
inline int n = 0;


//当前播放音乐的编号
inline int current_song_index = 0;

//快进/快退指数
inline  int play_argument = 5000;

//音量大小
inline int volume = 60;

