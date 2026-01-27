#include "Song.h"

Song::Song(string _path) {
    this->songPath = _path;
    parsePath();//调用函数解析
}
string Song::getPath() {
    return songPath;
}
string Song::getName() {
    return name;
}
string Song::getArtist() {
    return artist;
}
void Song::parsePath() {

}