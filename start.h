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
    my_play_list_controller.reload_current_list(songs_list);
    bool progressDragging = false;

    //加载并播放第一首歌
    std::string open_command = "open \"" + songs_list[0].song_address + "\" alias " + deviceName;
    mciSendString(open_command.c_str(), NULL, 0, NULL);
    std::string play_command = "play " + deviceName;
    mciSendString(play_command.c_str(),NULL, 0,NULL);

    unsigned long lastLClickTime = 0; // 左键
    unsigned long lastRClickTime = 0; // 右键
    while (true) {
        switch (condition) {
            case statu::main:
                flushmessage();
                drawMain(); //打印主菜单 初始化按钮 鼠标悬停改变按钮样式

                if (peekmessage(&msg,EX_MOUSE)) {
                    // 进度条拖拽
                    if (msg.message == WM_LBUTTONDOWN) {
                        // 检查是否点击了进度条区域
                        if (msg.x >= 0 && msg.x <= 1280 &&
                            msg.y >= 650 && msg.y <= 660) {  // 假设进度条高度5像素
                            progressDragging = true;
                            }
                        if (msg.x >= 1000 && msg.x <= 1280 &&
                            msg.y >= 725 && msg.y <= 730) {
                            dragging2 = true;
                            }
                    }
                    else if (msg.message == WM_LBUTTONUP) {
                        progressDragging = false;
                        dragging2 = false;
                    }
                    else if (msg.message == WM_MOUSEMOVE  ) {
                        // 拖动进度条 - 直接调用跳转函数
                        if (progressDragging) {
                            clickProgressBarToSeek(msg.x);
                        }
                        if (dragging2) {
                            // 拖动滑块
                            VolumeX = msg.x;
                            vol_flag = true;
                            if (VolumeX < 1000) VolumeX = 1000, vol_flag = false;
                            if (VolumeX > 1200) VolumeX = 1200;

                            // 计算新音量
                            int newVolume = (VolumeX - 1000)  / 2;
                            if (newVolume != volume) {
                                // 设置新音量
                                setVolume(newVolume);
                            }
                        }
                    }
                    //点击跳转
                    if (msg.message==WM_LBUTTONDOWN&&msg.y>=650&&msg.y<=660) {
                        clickProgressBarToSeek(msg.x);
                    }



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
                        fastBackward();
                        cout << "回退" << endl;
                    }

                    //单击快进
                    if (msg.message == WM_LBUTTONDOWN && button_forward.checkButton(msg.x, msg.y)) {
                        fastForward();
                        cout << "快进" << endl;
                    }

                    //单击上一曲
                    if (msg.message == WM_LBUTTONDOWN && button_previous.checkButton(msg.x, msg.y)) {
                        play_PreviousMusic();
                        cout << "上一曲" << endl;
                    }

                    //单击下一曲
                    if (msg.message == WM_LBUTTONDOWN && button_next.checkButton(msg.x, msg.y)) {
                        play_NextMusic();
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
                    //单击打开目录

                    if (msg.message == WM_LBUTTONDOWN && button_open_index.checkButton(msg.x, msg.y)) {
                        cout<<"打开目录"<<endl;
                        std::vector<Song>temp_song_list;
                        load_file(tinyfd_selectFolderDialog("选择文件夹", nullptr), temp_song_list);
                        my_play_list_controller.reload_current_list(temp_song_list);
                    }
                    //单击打开文件
                    if (msg.message == WM_LBUTTONDOWN && button_open_file.checkButton(msg.x, msg.y)) {
                        //load_simple_file();

                    }
                    //单击设置
                    if (msg.message == WM_LBUTTONDOWN && button_setting.checkButton(msg.x, msg.y)) {
                        condition = statu::setting;
                        flushmessage(EX_MOUSE);
                    }
                    if (my_play_list_controller.is_mouse_in_list_area(msg.x, msg.y)) {
                        switch (msg.message) {
                            case WM_MOUSEWHEEL:
                                my_play_list_controller.handle_wheel(msg.wheel, msg.x, msg.y);
                                break;

                            case WM_LBUTTONDOWN: {
                                unsigned long currentLClickTime = GetTickCount();
                                if (currentLClickTime - lastLClickTime < 500) {
                                    // L_click_index是song对象里面存储的index
                                    int L_click_index = my_play_list_controller.handle_click(msg.x, msg.y, false);
                                    if (L_click_index != -1) {
                                        // 播放歌曲可以在这里调用获取到的音乐路径播放歌曲
                                        play_music(L_click_index);
                                    }
                                    lastLClickTime = 0;
                                } else {
                                    lastLClickTime = currentLClickTime;
                                    my_play_list_controller.handle_click(msg.x, msg.y, false);
                                }
                            }
                                break;
                            case WM_RBUTTONDOWN: {
                                unsigned long currentRClickTime = GetTickCount();
                                if (currentRClickTime - lastRClickTime < 500) {
                                    int R_click_index = my_play_list_controller.handle_click(msg.x, msg.y, true);
                                    // int current_playlist_index = my_play_list_controller.get_current_playlist_index();
                                    // if (current_playlist_index == 1) {
                                    //     if (R_click_index >= 0 && R_click_index < songs_list.size()) {
                                    //         songs_list.erase(songs_list.begin() + R_click_index);
                                    //     }
                                    // }
                                    lastRClickTime = 0;
                                } else {
                                    lastRClickTime = currentRClickTime;
                                }
                            }
                                break;
                        }
                    }
                    if (play_statu==playStatu::play) {
                        checkAndPlayNext();
                    }
                    break;


                    case statu::setting:

                    drawSetting();
                    if (peekmessage(&msg,EX_MOUSE)) {
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
                                        setVolume(0);
                                        sliderX = 350;
                                        vol_flag = false;
                                        break;
                                    case false:
                                        setVolume(50);
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
                                setVolume(newVolume);
                            }
                        }
                        if (!setting.checkButton(msg.x, msg.y)) {
                            if (msg.message == WM_LBUTTONDOWN) {
                                condition = statu::main;
                            }
                        }
                    }
                    if (play_statu==playStatu::play) {
                        checkAndPlayNext();
                    }
                    flushmessage();
                    break;
                }
        }
    }
}
#endif
