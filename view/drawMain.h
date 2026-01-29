#pragma once
#include "../function/button.h"
#include <easyx.h>
#include "base.h"


//设置
button_img button_setting(30, 30, base_function, "sources/image/files_ui/btn_settings_down.png");
button_img button_setting_on(30, 30, base_function, "sources/image/files_ui/btn_settings_hover.png");
//播放
button_img button_pause(490, 650, base_function, "sources/image/control/btn_pause_norm.png");
button_img button_pause_on(490, 650, base_function, "sources/image/control/btn_pause_hover.png");
//回退
button_img button_backward(490 - wid, 650, base_function, "sources/image/control/btn_backward_norm.png");
button_img button_backward_on(490 - wid, 650, base_function, "sources/image/control/btn_backward_hover.png");
//快进
button_img button_forward(490 + wid, 650, base_function, "sources/image/control/btn_forward_norm.png");
button_img button_forward_on(490 + wid, 650, base_function, "sources/image/control/btn_forward_hover.png");
//下一首
button_img button_next(490 + 2 * wid, 650, base_function, "sources/image/control/btn_next_norm.png");
button_img button_next_on(490 + 2 * wid, 650, base_function, "sources/image/control/btn_next_hover.png");
//上一首
button_img button_previous(490 - wid * 2, 650, base_function, "sources/image/control/btn_prev_norm.png");
button_img button_previous_on(490 - wid * 2, 650, base_function, "sources/image/control/btn_prev_hover.png");
//顺序播放
button_img button_all(490 + 3 * wid, 650,base_function,"sources/image/audio_modes/btn_loop_all_down.png");
button_img button_all_on(490 + 3 * wid, 650,base_function,"sources/image/audio_modes/btn_loop_all_hover.png");
//单曲循环
button_img button_all_one(490 + 3 * wid, 650,base_function,"sources/image/audio_modes/btn_loop_one_down.png");
button_img button_all_one_on(490 + 3 * wid, 650,base_function,"sources/image/audio_modes/btn_loop_one_hover.png");
//随机播放
button_img button_random(490 + 3 * wid, 650,base_function,"sources/image/audio_modes/btn_shuffle_down.png");
button_img button_random_on(490 + 3 * wid, 650,base_function,"sources/image/audio_modes/btn_shuffle_hover.png");
//画出主界面
void drawMain() {
    BeginBatchDraw();
    loadimage(NULL, bk_img.c_str());

    //画出按钮
    if (button_setting.checkButton(msg.x, msg.y)) {
        button_setting_on.drawButton();
    } else {
        button_setting.drawButton();
    }

    if (button_pause.checkButton(msg.x, msg.y)) {
        button_pause_on.drawButton();
    } else {
        button_pause.drawButton();
    }

    if (button_backward.checkButton(msg.x, msg.y)) {
        button_backward_on.drawButton();
    } else {
        button_backward.drawButton();
    }

    if (button_forward.checkButton(msg.x, msg.y)) {
        button_forward_on.drawButton();
    } else {
        button_forward.drawButton();
    }

    if (button_next.checkButton(msg.x, msg.y)) {
        button_next_on.drawButton();
    } else {
        button_next.drawButton();
    }

    if (button_previous.checkButton(msg.x, msg.y)) {
        button_previous_on.drawButton();
    } else {
        button_previous.drawButton();
    }

    switch (play_mode) {
        case PlayMode::Sequence :
            if (button_all.checkButton(msg.x, msg.y)) {
                button_all_on.drawButton();
            } else {
                button_all.drawButton();
            }
            break;
        case  PlayMode::Random :
            if (button_random.checkButton(msg.x, msg.y)) {
                button_random_on.drawButton();
            } else {
                button_random.drawButton();
            }
            break;
        case  PlayMode::Sing_Loop:
            if (button_all_one.checkButton(msg.x, msg.y)) {
                button_all_one_on.drawButton();
            } else {
                button_all_one.drawButton();
            }
            break;

    }

    FlushBatchDraw();
    EndBatchDraw();
}
