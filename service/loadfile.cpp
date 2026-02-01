#include "loadfile.h"
#include <windows.h>
#include <filesystem>
#include <iostream>

#include "def.h"
namespace fs = std::filesystem;
std::string STRtoANSI(const std::string& str) {
    char ansi_path[MAX_PATH];
    wchar_t wide_path[MAX_PATH];
    // 将UTF-8转换为宽字符
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide_path, MAX_PATH);
    // 将宽字符转换为ANSI
    WideCharToMultiByte(CP_ACP, 0, wide_path, -1, ansi_path, MAX_PATH, NULL, NULL);

    return std::string(ansi_path);
}
void load_file(std::string songs_address,std::vector<Song> &songs_list) {

    //允许的后缀
    std::string name1 = "mp3";
    std::string name2 = "wav";
    //开始的编号
    int n =0;

    //读取文件，并写入数组
    for (const auto &entry: fs::directory_iterator(music_path)) {
        std::string temp = entry.path().string();
        std::string back = temp.substr(temp.size() - 3);
        if (back == name1 || back == name2) {
            std::string name = temp.substr(music_path.size(), temp.size() - music_path.size() - back.size()-1);
            char length[64];
            std::string cmd = "status "+songs_address+STRtoANSI(name)+"."+STRtoANSI(back)+" length";
            mciSendString(cmd.c_str(), length, sizeof(length), NULL);
            int total_ms = atoi(length);
            songs_list.push_back({n,STRtoANSI(name),songs_address+STRtoANSI(name)+"."+STRtoANSI(back),total_ms});
            n++;
        }
    }
    //打印测试
    for (auto i : songs_list) {
        std::cout<<i.song_index<<"||"<<i.song_name<<"||"<<i.song_address<<"||"<<i.song_time<<std::endl;
    }
}