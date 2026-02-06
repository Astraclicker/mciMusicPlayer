#pragma once
#include "../function/button.h"
#include "base.h"
#include "drawPlayList.h"
#include "easyx.h"


//设置
inline button_img button_setting(24, 23, 43, 43,WHITE, button_style::roundrect,
                                 "sources/image/files_ui/btn_settings_norm.png");
inline button_img button_setting_on(24, 23, 43, 43, WHITE, button_style::roundrect,
                                    "sources/image/files_ui/btn_settings_hover.png");
//播放
inline button_img button_play(605, 694, 70, 70,WHITE, button_style::roundrect,
                              "sources/image/control/btn_play_norm.png");
inline button_img button_play_on(605, 694, 70, 70,WHITE, button_style::roundrect,
                                 "sources/image/control/btn_play_hover.png");
//暂停
inline button_img button_pause(605, 694, 70, 70,WHITE, button_style::roundrect,
                               "sources/image/control/btn_pause_norm.png");
inline button_img button_pause_on(605, 694, 70, 70,WHITE, button_style::roundrect,
                                  "sources/image/control/btn_pause_hover.png");
//回退
inline button_img button_backward(439, 704, base_function, "sources/image/control/btn_backward_norm.png");
inline button_img button_backward_on(439, 704, base_function, "sources/image/control/btn_backward_hover.png");
//快进
inline button_img button_forward(791, 704, base_function, "sources/image/control/btn_forward_norm.png");
inline button_img button_forward_on(791, 704, base_function, "sources/image/control/btn_forward_hover.png");
//下一首
inline button_img button_next(708, 704, base_function, "sources/image/control/btn_next_norm.png");
inline button_img button_next_on(708, 704, base_function, "sources/image/control/btn_next_hover.png");
//上一首
inline button_img button_previous(522, 704, base_function, "sources/image/control/btn_prev_norm.png");
inline button_img button_previous_on(522, 704, base_function, "sources/image/control/btn_prev_hover.png");
//顺序播放
inline button_img button_all(323, 704, base_function, "sources/image/audio_modes/btn_loop_all_norm.png");
inline button_img button_all_on(323, 704, base_function, "sources/image/audio_modes/btn_loop_all_hover.png");
//单曲循环
inline button_img button_all_one(323, 704, base_function, "sources/image/audio_modes/btn_loop_one_norm.png");
inline button_img button_all_one_on(323, 704, base_function, "sources/image/audio_modes/btn_loop_one_hover.png");
//随机播放
inline button_img button_random(323, 704, base_function, "sources/image/audio_modes/btn_shuffle_norm.png");
inline button_img button_random_on(323, 704, base_function, "sources/image/audio_modes/btn_shuffle_hover.png");
//打开文件夹
inline button_img button_open_index(100, 25, 43, 96,WHITE, button_style::roundrect,
                                    "sources/image/files_ui/btn_add_folder_norm.png");
inline button_img button_open_index_on(100, 25, 43, 96,WHITE, button_style::roundrect,
                                       "sources/image/files_ui/btn_add_folder_hover.png");
//打开文件
inline button_img button_open_file(240, 25, 43, 126,WHITE, button_style::roundrect,
                                   "sources/image/files_ui/btn_add_file_norm.png");
inline button_img button_open_file_on(240, 25, 43, 126,WHITE, button_style::roundrect,
                                      "sources/image/files_ui/btn_add_file_hover.png");

//画出主界面
inline int VolumeX = 1120;
inline bool dragging2 = false;

void drawMain();
