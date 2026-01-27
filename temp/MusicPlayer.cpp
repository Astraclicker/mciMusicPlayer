#include "MusicPlayer.h"
MusicPlayer::MusicPlayer() {

}

void MusicPlayer::DrawALL() {
    cleardevice();

    ui.DrawMainScreen(manager);
    ui.DrawSetScreen();
    playButton.draw();
    nextButton.draw();

}
void  MusicPlayer::Handinput() {
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg,EM_MOUSE))
            if (msg.message == WM_LBUTTONDOWN) {

                //判断逻辑调用类的方法
                if (playBth.isClicked(msg.x,msg.y)) {



                    if (playBth.isClicked(msg.x,msg.y)) {

                    }

                }
            }

    }
}
void MusicPlayer::run() {
    initgraph();
    ui.InitResource();
    while (true) {

        Handinput();
        DrawALL();


    }

}