#pragma once
#include "../function/button.h"
#include <easyx.h>
#include "base.h"
#include "drawPlayList.h"


//设置
button_img button_setting(24, 23, base_function, "sources/image/files_ui/btn_settings_down.png");
button_img button_setting_on(24, 23, base_function, "sources/image/files_ui/btn_settings_hover.png");
//播放
button_img button_play (607,720,base_function,"sources/image/control/btn_play_norm.png");
button_img button_play_on (607,720,base_function,"sources/image/control/btn_play_hover.png");
//暂停
button_img button_pause(607,720, base_function, "sources/image/control/btn_pause_norm.png");
button_img button_pause_on(607,720, base_function, "sources/image/control/btn_pause_hover.png");
//回退
button_img button_backward(450,720, base_function, "sources/image/control/btn_backward_norm.png");
button_img button_backward_on(450,720, base_function, "sources/image/control/btn_backward_hover.png");
//快进
button_img button_forward(802,720, base_function, "sources/image/control/btn_forward_norm.png");
button_img button_forward_on(802,720, base_function, "sources/image/control/btn_forward_hover.png");
//下一首
button_img button_next(716,720, base_function, "sources/image/control/btn_next_norm.png");
button_img button_next_on(716,720, base_function, "sources/image/control/btn_next_hover.png");
//上一首
button_img button_previous(521,720, base_function, "sources/image/control/btn_prev_norm.png");
button_img button_previous_on(521,720, base_function, "sources/image/control/btn_prev_hover.png");
//顺序播放
button_img button_all(369,720,base_function,"sources/image/audio_modes/btn_loop_all_down.png");
button_img button_all_on(369,720,base_function,"sources/image/audio_modes/btn_loop_all_hover.png");
//单曲循环
button_img button_all_one(369,720,base_function,"sources/image/audio_modes/btn_loop_one_down.png");
button_img button_all_one_on(369,720,base_function,"sources/image/audio_modes/btn_loop_one_hover.png");
//随机播放
button_img button_random(369,720,base_function,"sources/image/audio_modes/btn_shuffle_down.png");
button_img button_random_on(369,720,base_function,"sources/image/audio_modes/btn_shuffle_hover.png");
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

    switch (play_statu) {
        case playStatu::pause :
            if (button_pause.checkButton(msg.x, msg.y)) {
                button_pause_on.drawButton();
            } else {
                button_pause.drawButton();
            }
            break;
        case playStatu::play :
            if (button_play.checkButton(msg.x, msg.y)) {
                button_play_on.drawButton();
            } else {
                button_play.drawButton();
            }
            break;
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

    defalt_playlist.draw();

    FlushBatchDraw();
    EndBatchDraw();
}
