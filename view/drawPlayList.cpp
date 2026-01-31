#include "drawPlayList.h"
#include "../service/Song.h"
#include "../function/button.h"
#include "easyx.h"



playlist::playlist() : songFont(22, 8, 0x333333, "Î¢ÈíÑÅºÚ") {
    this->playlist_button = new button_color(
        bg_playlist_x,
        bg_playlist_y,
        bg_playlist_H,
        bg_playlist_W,
        0xF5F5F5,
        button_style::roundrect
    );
}


playlist::~playlist() {
    if (playlist_button != nullptr) {
        delete playlist_button;
        playlist_button = nullptr;
    }
    for (auto btn: song_buttons) {
        delete btn;
    }
    song_buttons.clear();
}


void playlist::reload(const std::vector<Song> &songs_list_data) {
    for (auto btn: song_buttons) {
        delete btn;
    }
    song_buttons.clear();
    int current_y = bg_playlist_y + 10;
    int gap = 2;
    for (const auto &song: songs_list_data) {
        button_txt *new_btn = new button_txt(
            bg_playlist_x + 5, // x
            current_y, // y
            song.song_name, // text
            30, // length (°´Å¥¸ß¶È)
            bg_playlist_W - 10, // width
            RGB(130, 185, 255), // color (°´Å¥±³¾°É«)
            button_style::roundrect, // style
            this->songFont // font obj
        );
        song_buttons.push_back(new_btn);
        current_y += 30 + gap;
    }
}


void playlist::update_song_buttons(int wheel_move) {
    if (song_buttons.empty()) return;
    int speed = wheel_move / 120 * 40;
    if (speed == 0) return;
    int first_y = song_buttons.front()->get_y();
    int last_y = song_buttons.back()->get_y();
    int list_bottom = last_y + 30;
    int view_top = bg_playlist_y;
    int view_bottom = bg_playlist_y + bg_playlist_H;
    if (list_bottom - first_y <= bg_playlist_H) {
        return;
    }
    if (speed > 0) {
        if (first_y + speed > view_top) {
            speed = view_top - first_y;
        }
    } else if (speed < 0) {
        if (list_bottom + speed < view_bottom) {
            speed = view_bottom - list_bottom;
        }
    }
    for (auto btn: song_buttons) {
        int old_y = btn->get_y();
        btn->set_y(old_y + speed);
    }
}


void playlist::draw() {
    if (playlist_button) {
        playlist_button->drawButton();
    }
    int view_top = bg_playlist_y;
    int view_bottom = bg_playlist_y + bg_playlist_H;
    int j = 0;
    for (int i = 0; i < song_buttons.size(); i++) {
        int btn_y = song_buttons[i]->get_y();
        int btn_h = 30;
        if (btn_y >= view_top && btn_y + btn_h <= view_bottom) {
            song_buttons[i]->drawButton();
            j++;
        }
        if (j > 14) {return;}
    }
}

int playlist::is_clisk_button(int x, int y) {
    if (song_buttons.empty()) return -1;
    int inedex = 0;
    for (; inedex < song_buttons.size(); inedex++) {
        if (song_buttons[inedex]->checkButton(x, y))
            return inedex;
    }
    return -1;
}
