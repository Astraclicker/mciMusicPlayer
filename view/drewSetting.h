#pragma once
#include "../function/button.h"
#include "base.h"


//设置界面
inline button_color setting(width_window / 8, length_window / 8, base_setting);
//退出设置
inline button_txt exit_setting(190, 140, "退出", base_function_setting, CN);
inline button_txt exit_setting_on(190, 140, "退出", base_function_setting_on, CN);
//打开频谱
inline button_txt spectrum_setting(190, 220, "频谱", base_function_setting, CN);
inline button_txt spectrum_setting_on(190, 220, "频谱", base_function_setting_on, CN);
//音量打开
inline button_img volOn(300, 330, base_vol, "sources/image/audio_modes/btn_volume_on_down.png");
inline button_img volOn_on(300, 330, base_vol_on, "sources/image/audio_modes/btn_volume_on_hover.png");
//音量关闭
inline button_img volOff(300, 330, base_vol, "sources/image/audio_modes/btn_mute_down.png");
inline button_img volOff_on(300, 330, base_vol_on, "sources/image/audio_modes/btn_mute_hover.png");
//声明设备名称
inline std::string deviceName = "myaudio";
//滑块的坐标和点击状态
inline int sliderX = 470;
inline bool dragging = true;
inline bool vol_flag = true;

//MCI音量调节
void setVolume(int v);

//画出设置界面
void drawSetting();
