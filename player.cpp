// player.cpp - 带音量控制
#include "player.h"
#include <windows.h>
#include <string>

#pragma comment(lib, "winmm.lib")


// 播放列表相关实现
void Player::addToPlaylist(const std::string& filePath) {
    playlist.add(filePath);
}

int Player::playlistSize() const {
    return playlist.size();
}

std::string Player::getCurrentSong() const {
    return playlist.getCurrent();
}

void Player::playNext() {
    playlist.next();
    std::string song = playlist.getCurrent();
    if (!song.empty()) {
        close();
        load(song);
        play();
    }
}

void Player::playPrevious() {
    playlist.previous();
    std::string song = playlist.getCurrent();
    if (!song.empty()) {
        close();
        load(song);
        play();
    }
}

void Player::playAt(int index) {
    playlist.setCurrent(index);
    std::string song = playlist.getCurrent();
    if (!song.empty()) {
        close();
        load(song);
        play();
    }
}


bool Player::load(const std::string& filename) {
    close();
    std::string cmd = "open \"" + filename + "\" alias " + deviceName;
    if (mciSendString(cmd.c_str(), NULL, 0, NULL) == 0) {
        isPlaying = false;

        // 设置初始音量
        setVolume(70);  // 默认70%音量
        return true;
    }
    return false;
}

void Player::play() {
    if (isPlaying) return;
    std::string cmd = "play " + deviceName;
    mciSendString(cmd.c_str(), NULL, 0, NULL);
    isPlaying = true;
}

void Player::pause() {
    if (!isPlaying) return;
    std::string cmd = "pause " + deviceName;
    mciSendString(cmd.c_str(), NULL, 0, NULL);
    isPlaying = false;
}

void Player::stop() {
    std::string cmd = "stop " + deviceName;
    mciSendString(cmd.c_str(), NULL, 0, NULL);

    cmd = "seek " + deviceName + " to start";
    mciSendString(cmd.c_str(), NULL, 0, NULL);

    isPlaying = false;
}

void Player::toggle() {
    if (isPlaying) pause();
    else play();
}

bool Player::playing() const {
    return isPlaying;
}

void Player::close() {
    std::string cmd = "close " + deviceName;
    mciSendString(cmd.c_str(), NULL, 0, NULL);
    isPlaying = false;
}

// ============ 音量控制 ============
void Player::setVolume(int percent) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    volume=percent;
    // MCI音量设置 (0-1000)
    int mciVolume = percent * 10;
    char cmd[100];
    sprintf(cmd, "setaudio %s volume to %d", deviceName.c_str(), mciVolume);
    mciSendString(cmd, NULL, 0, NULL);
}



int Player::getVolume() const {
    // 简化：返回默认值，实际应该从MCI获取
    return volume;
}


