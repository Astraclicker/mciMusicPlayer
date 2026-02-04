#include "drawMain.h"
#include "drawAlbum.h"
#include "drawLyrics.h"

#include "../function/playMusic.h"
void drawMain() {
    BeginBatchDraw();
    loadimage(NULL, bk_img.c_str());

    IMAGE bilibili;
    loadimage(&bilibili,"sources/image/bilibili.png");
    putimage(-5,642,&bilibili);
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
    if (button_open_file.checkButton(msg.x,msg.y)) {
        button_open_file_on.drawButton();
    }else {
        button_open_file.drawButton();
    }
    if (button_open_index.checkButton(msg.x,msg.y)) {
        button_open_index_on.drawButton();
    }else {
        button_open_index.drawButton();
    }
    drawInformation();
    drawLyrics(current_song_index);
    drawAlbum(current_song_index);
    my_play_list_controller.draw_all();
    float progress = getProgress();
    drawSimpleProgressBar(0, 650, 1280, 10, progress);
    VolumeX=volume*2+1000;
    rectangle(1000, 725, 1200, 730);
    setfillcolor(RGB(38, 120, 255));
    fillrectangle(1000, 725, VolumeX, 730);
    setfillcolor(0x808080);
    solidcircle(VolumeX, 727.5, 8);
    char volText[20];
    sprintf(volText, "%d%%", volume);
    outtextxy(1220, 720, volText);

    FlushBatchDraw();
    EndBatchDraw();
}
