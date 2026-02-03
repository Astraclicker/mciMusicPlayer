#include "loadfile.h"
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <easyx.h>
#include "def.h"
namespace fs = std::filesystem;

std::string STRtoANSI(const std::string &str) {
    char ansi_path[MAX_PATH];
    wchar_t wide_path[MAX_PATH];
    // 将UTF-8转换为宽字符
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide_path, MAX_PATH);
    // 将宽字符转换为ANSI
    WideCharToMultiByte(CP_ACP, 0, wide_path, -1, ansi_path, MAX_PATH, NULL, NULL);

    return std::string(ansi_path);
}

void load_file(std::string music_address,std::vector<Song> &songs_list) {
    //允许的后缀
    std::string name1 = "mp3";
    std::string name2 = "wav";
    //对音乐路径进行预处理，把反斜杠换成正斜杠
    for (auto &str : music_address) {
        if (str=='\\') {
            str = '/';
        }
    }
    //读取文件，并写入数组
    for (const auto &entry: fs::directory_iterator(music_address)) {
        std::string temp = entry.path().string();
        std::string back = temp.substr(temp.size() - 3);
        if (back == name1 || back == name2) {
            std::string name = temp.substr(music_address.size()+1, temp.size() - music_address.size() - back.size() -2);
            char length[64];
            mciSendString("close myaudio", NULL, 0, NULL);
            std::string cmd = "open \"" + music_address +"/"+ STRtoANSI(name) + "." + STRtoANSI(back) + "\"  alias myaudio";
            mciSendString(cmd.c_str(), NULL, 0, NULL);
            mciSendString("status myaudio length", length, sizeof(length), NULL);
            int total_ms = atoi(length);
            songs_list.push_back({n, STRtoANSI(name),STRtoANSI(music_address), music_address +"/"+STRtoANSI(name) + "." + STRtoANSI(back), total_ms});
            n++;
        }
    }
    //打印测试
    for (auto i: songs_list) {
        std::cout << i.song_index << "||" << i.song_name << "||"<<i.song_root<<"||"<< i.song_address << "||" << i.song_time << std::endl;
    }
}

void load_simple_file(std::vector<Song> &songs_list) {
    // 定义文件过滤器
    const char *filterPatterns[] = {
        "*.mp3",
        "*.wav"
    };
    const char *filterDescription = "音乐文件 (*.mp3,*.wav)";

    const char *filePath = tinyfd_openFileDialog(
        "请选择音乐文件",
        NULL,
        2,
        filterPatterns,
        filterDescription,
        1
    );
    if (!filePath) {
        MessageBox(GetHWnd(), _T("然而你没有选择任何东西"), _T("callio"), MB_OK);
        return;
    }
    //对其颗粒度
    std::string a = filePath;
    std::string temp = a+"|";
    //降噪
    for (auto &str : temp) {
        if (str == '\\') {
            str = '/';
        }
    }

    while (!temp.empty()) {
        for (int i = 0;i<temp.size();i++) {
            if (temp[i]=='|') {
                std::string address = temp.substr(0,i);
                int j =0;
                auto k = address.end();
                while (*k != '/') {
                    k--;
                    j++;
                }
                std::string name = address.substr(address.size()-j+1,address.size());
                std::string root = address.substr(0,address.size()-j);
                char length[64];
                mciSendString("close myaudio", NULL, 0, NULL);
                std::string cmd = "open \"" +address+ "\"  alias myaudio";
                mciSendString(cmd.c_str(), NULL, 0, NULL);
                mciSendString("status myaudio length", length, sizeof(length), NULL);
                int total_ms = atoi(length);
                songs_list.push_back({n,name.erase(name.size()-4,4),root,address,total_ms});
                n++;
                temp.erase(0,i+1);
                break;
            }
        }
    }
    //打印测试
    for (auto i: songs_list) {
        std::cout << i.song_index << "||" << i.song_name << "||"<<i.song_root<<"||"<< i.song_address << "||" << i.song_time << std::endl;
    }
}