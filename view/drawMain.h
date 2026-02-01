#pragma once
#include "../function/button.h"
#include "base.h"
#include "drawPlayList.h"


//设置
inline button_img button_setting(24, 23, base_function, "sources/image/files_ui/btn_settings_down.png");
inline button_img button_setting_on(24, 23, base_function, "sources/image/files_ui/btn_settings_hover.png");
//播放
inline button_img button_play (607,720,base_function,"sources/image/control/btn_play_norm.png");
inline button_img button_play_on (607,720,base_function,"sources/image/control/btn_play_hover.png");
//暂停
inline button_img button_pause(607,720, base_function, "sources/image/control/btn_pause_norm.png");
inline button_img button_pause_on(607,720, base_function, "sources/image/control/btn_pause_hover.png");
//回退
inline button_img button_backward(450,720, base_function, "sources/image/control/btn_backward_norm.png");
inline button_img button_backward_on(450,720, base_function, "sources/image/control/btn_backward_hover.png");
//快进
inline button_img button_forward(802,720, base_function, "sources/image/control/btn_forward_norm.png");
inline button_img button_forward_on(802,720, base_function, "sources/image/control/btn_forward_hover.png");
//下一首
inline button_img button_next(716,720, base_function, "sources/image/control/btn_next_norm.png");
inline button_img button_next_on(716,720, base_function, "sources/image/control/btn_next_hover.png");
//上一首
inline button_img button_previous(521,720, base_function, "sources/image/control/btn_prev_norm.png");
inline button_img button_previous_on(521,720, base_function, "sources/image/control/btn_prev_hover.png");
//顺序播放
inline button_img button_all(369,720,base_function,"sources/image/audio_modes/btn_loop_all_down.png");
inline button_img button_all_on(369,720,base_function,"sources/image/audio_modes/btn_loop_all_hover.png");
//单曲循环
inline button_img button_all_one(369,720,base_function,"sources/image/audio_modes/btn_loop_one_down.png");
inline button_img button_all_one_on(369,720,base_function,"sources/image/audio_modes/btn_loop_one_hover.png");
//随机播放
inline button_img button_random(369,720,base_function,"sources/image/audio_modes/btn_shuffle_down.png");
inline button_img button_random_on(369,720,base_function,"sources/image/audio_modes/btn_shuffle_hover.png");
//画出主界面
void drawMain();