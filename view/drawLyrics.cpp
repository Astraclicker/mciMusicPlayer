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
    std::string CurrentPath = my_play_list_controller.get_current_song_root() + "/"+ my_play_list_controller.get_current_song_name() + ".lrc";

    std::ifstream lrc_file(CurrentPath);
    while (std::getline(lrc_file,text)) {
        //����ÿһ�и��
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
            lrc one_lrc;//һ�и�ʵĽṹ��
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

    //�����߼�
    int center_x= 421;
    int center_y= 317;
    int range = 4;
    int height = 40;

    for (int num = -range; num <= range; num++) {
        int real_index = current_index+num;
        if (real_index >= 0 && real_index < lrc_list.size()) {
            int draw_y = center_y + (num*height);
            if (num == 0) {
                settextcolor(RGB(30,144,255));
                settextstyle(20,0,"΢���ź�");
            }else {
                settextcolor(RGB(200, 200, 200));
                settextstyle(15,0,"΢���ź�");
            }
            setlinecolor(RGB(128,128,128));
            setlinestyle(PS_SOLID,2);
            line(405,114,405,554);
            // rectangle(510,114,935,564);
            setlinecolor(WHITE);
            setlinestyle(PS_SOLID,1);
            outtextxy(center_x,draw_y,lrc_list[real_index].title.c_str());
        }
    }
}
void drawInformation() {
    std::string artist_song = my_play_list_controller.get_current_song_name();
    int pos = artist_song.find('-');
    std::string artist = artist_song.substr(0,pos);
    std::string song_name = artist_song.substr(pos+1);
    settextcolor(BLACK);
    settextstyle(25,0,"微软雅黑");
    outtextxy(31,504,artist.c_str());
    settextcolor(RGB(128,128,128));
    settextstyle(20,0,"微软雅黑");
    outtextxy(31,534,song_name.c_str());

}
