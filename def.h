/*
*为程序提供宏
 *枚举
 */
#pragma once
//窗口大小
constexpr int width_window =1080;
constexpr int  length_window= 720;

inline extern std::string bk_img ("sources/img/background.png");

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