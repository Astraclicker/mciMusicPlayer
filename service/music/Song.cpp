#include "Song.h"

Song::Song(string songPath) {
    this->songPath = songPath;
    parsePath();//调用函数解析
}
string Song::getPath() {
    return songPath;
}
string Song::getName() {
    string name;
    return name;
}

void Song::parsePath() {

}