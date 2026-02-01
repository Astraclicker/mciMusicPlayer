#include "playMusic.h"
#include <windows.h>
//暂停/播放控件
void control_music (playStatu&status) {
    if (status == playStatu::pause) {
        // 暂停 -> 播放
        mciSendString("play myaudio", NULL, 0, NULL);
        status = playStatu::play;
    }
    else { // status == PlayStatus::play
        // 播放 -> 暂停
        mciSendString("pause myaudio", NULL, 0, NULL);
        status = playStatu::pause;
    }
}

//播放音乐
void play_music (std::vector<Song> &songs_list,int *index) {
}

//播放下一曲/上一曲
void play_NextMusic(std::vector<Song> &songs_list,int *index,PlayMode play_mode) {

}

//快进/快退
void play_music_argument(std::vector<Song> &songs_list,int index,int play_argument) {

}

//快进/快退指数转换
int change_argument(std::vector<Song> &songs_list,int index,int x) {

}