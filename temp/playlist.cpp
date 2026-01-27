// playlist.cpp - 简单实现
#include "playlist.h"

void Playlist::add(const std::string& filePath) {
    songs.push_back(filePath);
    if (currentIndex == -1) {
        currentIndex = 0;
    }
}

int Playlist::size() const {
    return songs.size();
}

int Playlist::getCurrentIndex() const {
    return currentIndex;
}

std::string Playlist::getCurrent() const {
    if (currentIndex >= 0 && currentIndex < songs.size()) {
        return songs[currentIndex];
    }
    return "";
}

void Playlist::next() {
    if (songs.empty()) return;
    currentIndex = (currentIndex + 1) % songs.size();
}

void Playlist::previous() {
    if (songs.empty()) return;
    currentIndex = (currentIndex - 1 + songs.size()) % songs.size();
}

void Playlist::setCurrent(int index) {
    if (index >= 0 && index < songs.size()) {
        currentIndex = index;
    }
}