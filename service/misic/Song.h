#pragma once
#include <iostream>
#include <string>

using namespace std;
//存放歌曲数据信息
class Song {
private:
        string name;//歌名
        string artist;//歌手
        string songPath;//路径


public:
        Song(string _path);
        string getPath();
        string getName();
        string getArtist();

private:
    //从路径提取信息
    void parsePath();

};