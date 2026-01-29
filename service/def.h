/*
*为程序提供宏
 *枚举
 */
#pragma once

#include <vector>

//窗口大小
constexpr int wid =90;
constexpr int width_window =1080;
constexpr int  length_window= 720;

inline std::string music_path = "sources";  //音乐路径
inline std::string bk_img = "sources/image/bk.png";//播放按钮

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

//声明状态机
inline statu condition;

//播放列表
inline std::vector<std::string>songs_list;