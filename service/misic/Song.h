#pragma once
#include <iostream>
#include <string>

using namespace std;
//存放歌曲数据信息
typedef struct music {
    string name;//歌名
    string artist;//歌手
    string songPath;//路径
    int time;//歌曲时间
}music;
//我实在找不到应该从哪里开始读取文件 我就写成结构体了

class Song {//存放选择当前播放文件？
private:
    string name;//歌名
    string artist;//歌手
    string songPath;//路径
    int time;//歌曲时间
public:
        Song(string _path);
        string getPath();
        string getName();
        string getArtist();

private:
    //从路径提取信息
    void parsePath();

};