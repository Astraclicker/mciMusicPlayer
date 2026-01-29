#pragma once
#include <iostream>
#include <string>

using namespace std;
//存放歌曲数据信息
class Song {

protected:
        string songName;//歌名
        string songPath;//路径
public:
        Song(string songPath);
        string getPath();
        string getName();
        string getArtist();

private:
    //从路径提取信息
    void parsePath();

};