#include "drawLyrics.h"
#include <easyx.h>
#include "drawPlayList.h"
#include <fstream>
#include <iostream>
#include "drewSetting.h"
#include "../service/loadfile.h"

long long getCurrenTime() {
    char time[100] = {0};
    std::string command = "status " + deviceName + " position";
    mciSendString(command.c_str(),time,100,NULL);
    long long current_time = std::atoll(time);
    return current_time;
}
void loadLyrics() {
    lrc_list.clear();
    std::string CurrentPath = music_path + "/"+ my_play_list_controller.get_current_song_name() + ".lrc";

    std::ifstream lrc_file(CurrentPath);
    while (std::getline(lrc_file,text)) {
        //解析每一行歌词
        int pos = text.find(']');
        std::string temp = text.substr(pos+1);
        std::string word = STRtoANSI(temp);
        try {
            std::string min_str= text.substr(1,2);
            int minute = std::stoi(min_str);
            std::string second_str =  text.substr(4,2);
            int second = std::stoi(second_str);
            std::string third_str = text.substr(7,2);
            int third = std::stoi(third_str);
            long long total_time;
            total_time = minute*60*1000 + second*1000 + third*10;
            lrc one_lrc;//一行歌词的结构体
            one_lrc.time = total_time;
            one_lrc.title = word;
            lrc_list.push_back(one_lrc);
        }catch (...) {
            continue;
        }
    }
    lrc_file.close();
}
void drawLyrics(int index) {
    int current_index = 0;
    long long current_time = getCurrenTime();
    for (int i = 0; i < lrc_list.size(); i++) {
        if (lrc_list[i].time > current_time) {
            current_index = i-1;
            break;
        }
        current_index = i;
    }

    //绘制逻辑
    int center_x= 520;
    int center_y= 317;
    int range = 4;
    int height = 40;

    for (int num = -range; num <= range; num++) {
        int real_index = current_index+num;
        if (real_index >= 0 && real_index < lrc_list.size()) {
            int draw_y = center_y + (num*height);
            if (num == 0) {
                settextcolor(RGB(30,144,255));
                settextstyle(35,0,"微软雅黑");
            }else {
                settextcolor(RGB(200, 200, 200));
                settextstyle(20,0,"微软雅黑");
            }
            setlinecolor(RGB(30,144,255));
            setlinestyle(PS_SOLID,2);
            rectangle(510,114,935,564);
            setlinecolor(WHITE);
            setlinestyle(PS_SOLID,1);
            outtextxy(center_x,draw_y,lrc_list[real_index].title.c_str());
        }
    }
}
