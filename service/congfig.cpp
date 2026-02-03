#include "congfig.h"
#include <iostream>
#include <fstream>
#include "../view/drawPlayList.h"
#include <vector>

using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;
using std::string;
using std::vector;


void writeString(ofstream& file, const string& str) {
    size_t len = str.size();
    file.write((char*)&len, sizeof(size_t));
    if (len > 0) file.write(str.c_str(), len);
}

void readString(ifstream& file, string& str) {
    size_t len;
    file.read((char*)&len, sizeof(size_t));
    if (len > 0) {
        str.resize(len);
        file.read(&str[0], len);
    } else {
        str = "";
    }
}

bool save_config() {
    string filename = "config.dat";
    // 创建config.dat文件
    ofstream file(filename, ios::out | ios::binary);
    if (!file) return false;
    // 保存当前所在的播放列是哪里
    int current_idx = my_play_list_controller.current_playlist_index;
    file.write((char*)&current_idx, sizeof(int));
    // 保存播放列表个数
    size_t playlist_count = my_play_list_controller.tabs.size() - 1;
    if (my_play_list_controller.tabs.size() == 0) playlist_count = 0;
    file.write((char*)&playlist_count, sizeof(size_t));

    // 遍历 tabs 挨个保存每个播放列表的相关信息
    for (size_t i = 1; i < my_play_list_controller.tabs.size(); i++) {
        playlist* pl = my_play_list_controller.tabs[i].list_obj;
        // 如果播放列表为空就存个0进去
        if (!pl) {
            size_t zero = 0;
            file.write((char*)&zero, sizeof(size_t));
            continue;
        }

        // 保存该播放列表的歌曲数量
        size_t song_count = pl->playlist_songs.size();
        file.write((char*)&song_count, sizeof(size_t));

        // 遍历保存每首歌
        for (const auto& item : pl->playlist_songs) {
            const Song& s = item.song;

            // 存基本类型
            file.write((char*)&s.song_index, sizeof(int));
            file.write((char*)&s.song_time, sizeof(int));
            writeString(file, s.song_name);
            writeString(file, s.song_root);
            writeString(file, s.song_address);

        }
    }

    file.close();
    cout << "Config saved successfully!" << endl;
    return true;
}

bool load_config() {
    // 查找是否有配置文件
    string filename = "config.dat";
    ifstream file(filename, ios::in | ios::binary);
    // 检查是否真的打开文件了
    if (!file) {
        cout << "Config file not found." << endl;
        return false;
    }

    int saved_current_index = 1;
    file.read((char*)&saved_current_index, sizeof(int));

    size_t playlist_count = 0;
    file.read((char*)&playlist_count, sizeof(size_t));

    // 清理旧歌单
    // 从后往前删，保留第0个
    for (int i = my_play_list_controller.tabs.size() - 1; i >= 1; i--) {
        my_play_list_controller.delete_playlist_tab_for_load_config(i);
    }

    // 重建歌单
    for (size_t i = 0; i < playlist_count; i++) {
        // 根据保存到的playlist_song现场建立歌单
        my_play_list_controller.add_playlist_tab();
        // 获取新创建的 playlist 对象
        playlist* current_pl = my_play_list_controller.tabs.back().list_obj;

        size_t song_count = 0;
        file.read((char*)&song_count, sizeof(size_t));

        vector<Song> temp_songs;
        temp_songs.reserve(song_count);

        for (size_t j = 0; j < song_count; j++) {
            Song s;
            // 重点，每次读取完需要的信息，他会自动往后面跑
            //
            file.read((char*)&s.song_index, sizeof(int));
            file.read((char*)&s.song_time, sizeof(int));
            readString(file, s.song_name);
            readString(file, s.song_root);
            readString(file, s.song_address);


            temp_songs.push_back(s);
        }
        // 根据读取到到的歌单，调用load函数现场将歌单加载到播放列表
        if (current_pl) {
            current_pl->load(temp_songs);
        }
    }
    // 检测读取到的播放列表是否有效，若有效则切换到对应的播放列表
    if (saved_current_index > 0 && saved_current_index < my_play_list_controller.tabs.size()) {
        my_play_list_controller.switch_tab(saved_current_index);
    } else {
        my_play_list_controller.switch_tab(1);
    }

    file.close();
    cout << "Config loaded successfully!" << endl;
    return true;
}
