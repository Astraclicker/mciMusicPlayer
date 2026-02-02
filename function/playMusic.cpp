#include "playMusic.h"
#include <windows.h>
#include "../view/drawPlayList.h"
//暂停/播放控件
void control_music (playStatu&status) {
    if (status == playStatu::pause) {
        // 暂停 -> 播放
        mciSendString("play myaudio", NULL, 0, NULL);
        status = playStatu::play;
    }
    else { // status == PlayStatus::play
        // 播放 -> 暂停
        mciSendString("stop myaudio", NULL, 0, NULL);
        status = playStatu::pause;
    }
}

void play_music (int newindex) {
    if (newindex < 0 || newindex >= my_play_list_controller.get_current_playlist_size()) return;
    current_song_index = newindex;
    // 停止当前播放
    mciSendString("close myaudio", NULL, 0, NULL);

    // 打开新歌曲
    std::string cmd = "open \"" + my_play_list_controller.get_current_song_path(current_song_index) + "\" alias myaudio";
    mciSendString(cmd.c_str(), NULL, 0, NULL);

    // 播放
    mciSendString("play myaudio", NULL, 0, NULL);
    play_statu = playStatu::play;
}

//播放下一曲/上一曲
void play_NextMusic() {
    switch (play_mode) {
        case PlayMode::Sequence:
            current_song_index = current_song_index + 1;
            if (current_song_index >= my_play_list_controller.get_current_playlist_size()) {
                current_song_index = 0;  // 循环到第一首
            }
            break;
        case PlayMode::Sing_Loop:
            //index=index不变
            break;
        case PlayMode::Random:
            current_song_index=rand() % my_play_list_controller.get_current_playlist_size() ;
            break;
    }
    play_music(current_song_index);
}

void play_PreviousMusic() {
    switch (play_mode) {
        case PlayMode::Sequence:
            current_song_index=current_song_index - 1;
            if (current_song_index < 0) {
                current_song_index = my_play_list_controller.get_current_playlist_size() - 1;  // 循环到最后一首
            }
            break;
        case PlayMode::Sing_Loop:
            //index=index不变
            break;
        case PlayMode::Random:
            current_song_index=rand() % my_play_list_controller.get_current_playlist_size() ;
            break;
    }
    play_music(current_song_index);
}

//快进/快退
void play_music_argument(std::vector<Song> &songs_list,int index,int play_argument) {

}

//快进/快退指数转换
int change_argument(std::vector<Song> &songs_list,int index,int x) {

}