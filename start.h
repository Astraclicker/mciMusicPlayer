#ifndef MCIMUSICPLAYER_START_H
#define MCIMUSICPLAYER_START_H
#include <easyx.h>
#include "view/drawMain.h"
#include "view/drewSetting.h"
#include "service/def.h"
#include <iostream>
#include "view/drawPlayList.h"
#include "function/playMusic.h"
#include "service/loadfile.h"
using std::cout;
using std::endl;

void start() {
    initgraph(width_window, length_window);
    condition = statu::main;
    play_statu = playStatu::play;
    play_mode = PlayMode::Sequence;
    load_file(music_path, songs_list);
    defalt_playlist.reload(songs_list); // 播放列表测试使用

    while (true) {
        switch (condition) {
            case statu::main:
                flushmessage();
                drawMain(); //打印主菜单 初始化按钮 鼠标悬停改变按钮样式
                getmessage(&msg);
                //单击设置
                if (msg.message == WM_LBUTTONDOWN && button_setting.checkButton(msg.x, msg.y)) {
                    cout << "设置" << endl;
                    condition = statu::setting; //改变状态器 为设置界面
                    flushmessage(EX_MOUSE);
                }

                //单击暂停/播放
                if (msg.message == WM_LBUTTONDOWN && button_pause.checkButton(msg.x, msg.y)) {
                    cout << "播放暂停" << endl;
                    control_music(play_statu);
                }

                //单击回退
                if (msg.message == WM_LBUTTONDOWN && button_backward.checkButton(msg.x, msg.y)) {
                    cout << "回退" << endl;
                }

                //单击快进
                if (msg.message == WM_LBUTTONDOWN && button_forward.checkButton(msg.x, msg.y)) {
                    cout << "快进" << endl;
                }

                //单击上一曲
                if (msg.message == WM_LBUTTONDOWN && button_previous.checkButton(msg.x, msg.y)) {
                    cout << "上一曲" << endl;
                }

                //单击下一曲
                if (msg.message == WM_LBUTTONDOWN && button_next.checkButton(msg.x, msg.y)) {
                    cout << "下一曲" << endl;
                }

                //单击播放模式切换
                if (msg.message == WM_LBUTTONDOWN && button_all_on.checkButton(msg.x, msg.y)) {
                    switch (play_mode) {
                        case PlayMode::Random:
                            play_mode = PlayMode::Sing_Loop;
                            break;
                        case PlayMode::Sequence:
                            play_mode = PlayMode::Random;
                            break;
                        case PlayMode::Sing_Loop:
                            play_mode = PlayMode::Sequence;
                            break;
                    }
                }
                if (msg.x > bg_playlist_x && msg.x < bg_playlist_x + bg_playlist_W &&
                    msg.y > bg_playlist_y && msg.y < bg_playlist_y + bg_playlist_H) {
                    if (msg.message == WM_MOUSEWHEEL) {
                        defalt_playlist.update_song_buttons(msg.wheel);
                    }
                    if (msg.message == WM_LBUTTONDOWN) {
                        int index = defalt_playlist.is_clisk_button(msg.x, msg.y);
                        cout << index << endl;
                    }
                }

                break;


            case statu::setting:

                drawSetting();
                getmessage(&msg);
                if (msg.message == WM_LBUTTONDOWN) {
                    cout << msg.x << "||" << msg.y << endl;

                    if (exit_setting.checkButton(msg.x, msg.y)) {
                        condition = statu::main;
                    }
                    if (spectrum_setting.checkButton(msg.x, msg.y)) {
                        system("start sources/cava/cava.exe");
                    }
                    if (volOn.checkButton(msg.x, msg.y)) {
                        switch (vol_flag) {
                            //根据值 改变play_mode的状态
                            case true:
                                setVloume(0);
                                sliderX = 350;
                                vol_flag = false;
                                break;
                            case false:
                                setVloume(50);
                                sliderX = 400;
                                vol_flag = true;
                                break;
                        }
                    }
                    if (msg.x >= 350 && msg.x <= 550 &&
                        msg.y >= 350 && msg.y <= 355) {
                        dragging = true;
                    }
                } else if (msg.message == WM_LBUTTONUP) {
                    dragging = false;
                } else if (msg.message == WM_MOUSEMOVE && dragging) {
                    // 拖动滑块
                    sliderX = msg.x;
                    vol_flag = true;
                    if (sliderX < 350) sliderX = 350, vol_flag = false;
                    if (sliderX > 550) sliderX = 550;

                    // 计算新音量
                    int newVolume = (sliderX - 350) * 100 / 200;
                    if (newVolume != volume) {
                        // 设置新音量
                        setVloume(newVolume);
                    }
                }
                if (!setting.checkButton(msg.x, msg.y)) {
                    if (msg.message == WM_LBUTTONDOWN) {
                        condition = statu::main;
                    }
                }
                flushmessage();
                break;
        }
    }
}
#endif
