#include "drawMain.h"
#include "drawAlbum.h"
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
            if (button_play.checkButton(msg.x, msg.y)) {
                button_play_on.drawButton();
            } else {
                button_play.drawButton();
            }
            break;
        case playStatu::play :
            if (button_pause.checkButton(msg.x, msg.y)) {
                button_pause_on.drawButton();
            } else {
                button_pause.drawButton();
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
    drawAlbum(songs_list,index);
    // 该函数有空白遮罩，添加歌曲，添加目录，进度条，歌词打印以及后续如果会移动到主界面的音量条
    // 都请在后面绘制
    // 否则会被空白遮罩遮住
    my_play_list_controller.draw_all();
    FlushBatchDraw();
    EndBatchDraw();
}
