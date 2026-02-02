#include "drawPlayList.h"
#include "base.h"
#include <iostream>

using std::cout;
using std::endl;


// ==========================================================
// play_list
// ==========================================================

playlist::playlist() : songFont(22, 8, 0x333333, "Œ¢»Ì—≈∫⁄") {
    this->bg_playlist_x = 952;
    this->bg_playlist_y = 109;
    this->bg_playlist_W = 316;
    this->bg_playlist_H = 520;
    this->song_button_H = 30;
    this->song_button_gap = 2;

    this->bg_button = new button_color(
        this->bg_playlist_x, this->bg_playlist_y,
        this->bg_playlist_H, this->bg_playlist_W,
        0xF5F5F5, button_style::roundrect
    );
}

playlist::~playlist() {
    if (bg_button) delete bg_button;
    for (auto &item : playlist_songs) {
        if (item.playlist_button) delete item.playlist_button;
    }
    playlist_songs.clear();
}

void playlist::reload(const std::vector<Song> &songs_list_data) {
    // 1. «Â¿Ì
    for (auto &item : playlist_songs) {
        if (item.playlist_button) delete item.playlist_button;
    }
    playlist_songs.clear();

    int current_y = bg_playlist_y + 10;
    for (const auto &song_data : songs_list_data) {
        button_txt *new_btn = new button_txt(
            bg_playlist_x + 5, current_y,
            song_data.song_name, 30,
            bg_playlist_W - 10,
            RGB(130, 185, 255),
            button_style::roundrect, songFont
        );

        playlist_song new_item;
        new_item.song = song_data;
        new_item.playlist_button = new_btn;
        playlist_songs.push_back(new_item);

        current_y += song_button_H + song_button_gap;
    }
}

void playlist::add_song(const Song &song) {
    int new_y = bg_playlist_y + 10;
    if (!playlist_songs.empty()) {
        new_y = playlist_songs.back().playlist_button->get_y() + song_button_H + song_button_gap;
    }
    button_txt *new_btn = new button_txt(
        bg_playlist_x + 5, new_y,
        song.song_name, 30,
        bg_playlist_W - 10,
        RGB(130, 185, 255),
        button_style::roundrect, songFont
    );
    playlist_songs.push_back({song, new_btn});
}

void playlist::update_song_buttons_y(int wheel_move) {
    if (playlist_songs.empty()) return;

    int speed = wheel_move / 120 * 40;
    if (speed == 0) return;

    int first_y = playlist_songs.front().playlist_button->get_y();
    int last_y = playlist_songs.back().playlist_button->get_y();
    int list_bottom = last_y + song_button_H;
    int view_top = bg_playlist_y + 10;
    int view_bottom = bg_playlist_y + bg_playlist_H - 10;

    if (list_bottom - first_y <= bg_playlist_H) return;

    if (speed > 0 && first_y + speed > view_top) speed = view_top - first_y;
    else if (speed < 0 && list_bottom + speed < view_bottom) speed = view_bottom - list_bottom;

    for (auto &item : playlist_songs) {
        item.playlist_button->set_y(item.playlist_button->get_y() + speed);
    }
}

void playlist::draw() {
    if (bg_button) bg_button->drawButton();

    int view_top = bg_playlist_y + 5;
    int view_bottom = bg_playlist_y + bg_playlist_H - 5;

    for (auto &item : playlist_songs) {
        int y = item.playlist_button->get_y();
        if (y + song_button_H > view_top && y < view_bottom) {
            item.playlist_button->drawButton();
        }
    }

    // ªÊ÷∆’⁄’÷
    COLORREF last_fill = getfillcolor();
    COLORREF last_line = getlinecolor();
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    // …œ’⁄’÷
    solidrectangle(bg_playlist_x, view_top - 30, bg_playlist_x + bg_playlist_W, view_top);
    // œ¬’⁄’÷
    solidrectangle(bg_playlist_x, view_bottom, bg_playlist_x + bg_playlist_W, view_bottom + 30);
    setfillcolor(last_fill);
    setlinecolor(last_line);
}

int playlist::get_songs_list_index(int clicked_song_index) {
    return playlist_songs[clicked_song_index].song.song_index;
}



int playlist::is_click_button(int x, int y) {
    if (x < bg_playlist_x || x > bg_playlist_x + bg_playlist_W ||
        y < bg_playlist_y || y > bg_playlist_y + bg_playlist_H) {
        return -1;
    }
    for (int i = 0; i < playlist_songs.size(); i++) {
        if (playlist_songs[i].playlist_button->checkButton(x, y)) return i;
    }
    return -1;
}

void playlist::delete_song_from_current_playlist(int current_song_index) {
    if (current_song_index < 0 || current_song_index >= playlist_songs.size()) return;

    int current_y = playlist_songs[current_song_index].playlist_button->get_y();
    delete playlist_songs[current_song_index].playlist_button;
    playlist_songs.erase(playlist_songs.begin() + current_song_index);
    
    for (int i = current_song_index; i < playlist_songs.size(); i++) {
        playlist_songs[i].playlist_button->set_y(current_y);
        current_y += song_button_H + song_button_gap;
    }
}

std::string playlist::get_song_address(int current_song_index) {
    if (current_song_index >= 0 && current_song_index < playlist_songs.size()) {
        return playlist_songs[current_song_index].song.song_address;
    }
    return "";
}


// ==========================================================
// play_list_controller
// ==========================================================

play_list_controller::play_list_controller() : tabFont(22, 8, 0x333333, "Œ¢»Ì—≈∫⁄") {
    ctrl_x = 952; ctrl_y = 69; ctrl_w = 316; ctrl_h = 40;
    tab_btn_w = 80; tab_btn_h = 30;
    current_playlist_index = 1;

    bg_button = new button_color(ctrl_x, ctrl_y, ctrl_h, ctrl_w, 0xE0E0E0, button_style::roundrect);


    PlaylistTab add_tab;
    add_tab.tab_button = new button_txt(
        ctrl_x + 5, ctrl_y + 5, "+", tab_btn_h, 30,
        RGB(130, 185, 255), button_style::roundrect, txt(22, 8, 0x000000, "Œ¢»Ì—≈∫⁄")
    );
    add_tab.list_obj = nullptr;
    tabs.push_back(add_tab);


    add_playlist_tab();

    delete tabs[1].tab_button;
    tabs[1].tab_button = new button_txt(
        ctrl_x + 5 + 30 + 2, ctrl_y + 5, "ƒ¨»œ¡–±Ì",
        tab_btn_h, tab_btn_w, RGB(130, 185, 255), button_style::roundrect, tabFont
    );
}

play_list_controller::~play_list_controller() {
    if (bg_button) delete bg_button;
    for (auto &tab : tabs) {
        if (tab.tab_button) delete tab.tab_button;
        if (tab.list_obj) delete tab.list_obj;
    }
    tabs.clear();
}

void play_list_controller::reload_current_list(const std::vector<Song> &global_data) {

    if (tabs.size() <= 1) {
        if (tabs.empty()) {

        }
        add_playlist_tab();
        current_playlist_index = 1;
    }

    if (current_playlist_index < 1 || current_playlist_index >= tabs.size()) {
        current_playlist_index = 1;
    }

    if (tabs[current_playlist_index].list_obj) {
        tabs[current_playlist_index].list_obj->reload(global_data);
        cout << "Loaded " << global_data.size() << " songs into Tab " << current_playlist_index << endl;
    }
}

void play_list_controller::add_playlist_tab() {
    int new_x = ctrl_x + 5;
    if (!tabs.empty()) {
        button_txt* last = tabs.back().tab_button;
        int last_w = (tabs.size() == 1) ? 30 : tab_btn_w;
        new_x = last->get_x() + last_w + 2;
    }

    std::string name = "∏Ëµ•" + std::to_string(tabs.size());
    button_txt* new_btn = new button_txt(
        new_x, ctrl_y + 5, name, tab_btn_h, tab_btn_w,
        RGB(130, 185, 255), button_style::roundrect, tabFont
    );

    PlaylistTab new_tab;
    new_tab.tab_button = new_btn;
    new_tab.list_obj = new playlist();

    tabs.push_back(new_tab);
}

void play_list_controller::delete_playlist_tab(int index) {
    if (index <= 0 || index >= tabs.size()) return;

    int current_x = tabs[index].tab_button->get_x();

    delete tabs[index].tab_button;
    delete tabs[index].list_obj;
    tabs.erase(tabs.begin() + index);

    if (current_playlist_index == index) {
        current_playlist_index = index - 1;
        if (current_playlist_index < 1 && tabs.size() > 1) current_playlist_index = 1;
    }
    else if (current_playlist_index > index) {
        current_playlist_index--;
    }

    for (int i = index; i < tabs.size(); i++) {
        tabs[i].tab_button->set_x(current_x);
        current_x += tab_btn_w + 2;
    }
}

void play_list_controller::switch_tab(int index) {
    if (index > 0 && index < tabs.size()) {
        current_playlist_index = index;
        cout << "Switched to Tab: " << index << endl;
    }
}

void play_list_controller::add_song_to_current_list(const Song& new_song) const {
    if (current_playlist_index > 0 && current_playlist_index < tabs.size()) {
        playlist* current_list = tabs[current_playlist_index].list_obj;
        if (current_list) {
            current_list->add_song(new_song);
            cout << "Successfully added [" << new_song.song_name << "] to playlist " << current_playlist_index << endl;
        }
    } else {
        cout << "Error: Cannot add song to current tab (maybe it's the '+' button?)" << endl;
    }
}

int play_list_controller::handle_click(int x, int y, bool is_right_click) {
    if (y >= ctrl_y && y <= ctrl_y + ctrl_h) {
        for (int i = 0; i < tabs.size(); i++) {
            if (tabs[i].tab_button->checkButton(x, y)) {
                if (is_right_click) {
                    cout << "Deleting Playlist: " << i << endl;
                    delete_playlist_tab(i);
                } else {
                    if (i == 0) {
                        cout << "Add new playlist" << endl;
                        add_playlist_tab();
                    } else {
                        switch_tab(i);
                    }
                }
                return -1;
            }
        }
    }
    if (current_playlist_index > 0 && current_playlist_index < tabs.size()) {
        playlist* current_list = tabs[current_playlist_index].list_obj;
        if (current_list) {
            int song_idx = current_list->is_click_button(x, y);
            if (song_idx != -1) {
                if (is_right_click) {
                    cout << "Removing song " << song_idx << " from list " << current_playlist_index << endl;
                    current_list->delete_song_from_current_playlist(song_idx);
                    return song_idx;
                }else {
                    // À´ª˜◊Ûº¸∑µªÿsong¿Ô√Êµƒindex
                    return song_idx;
                }
            }
        }
    }
    return -1;
}

void play_list_controller::handle_wheel(int wheel_move, int mouse_x, int mouse_y) {
    if (mouse_y >= ctrl_y && mouse_y <= ctrl_y + ctrl_h) {
        if (tabs.empty()) return;
        int speed = wheel_move / 120 * 20;
        if (speed == 0) return;
        int first_x = tabs.front().tab_button->get_x();
        int last_w = (tabs.size() == 1) ? 30 : tab_btn_w;
        int last_x = tabs.back().tab_button->get_x();
        int list_right = last_x + last_w;
        int view_left = ctrl_x + 5;
        int view_right = ctrl_x + ctrl_w - 5;
        int view_width = view_right - view_left;

        if (list_right - first_x <= view_width) return;
        if (speed > 0) {
            if (first_x + speed > view_left) {
                speed = view_left - first_x;
            }
        }
        else if (speed < 0) {
            if (list_right + speed < view_right) {
                speed = view_right - list_right;
            }
        }
        if (speed == 0) return;
        for (auto &t : tabs) {
            t.tab_button->set_x(t.tab_button->get_x() + speed);
        }
    }
    else if (current_playlist_index > 0 && current_playlist_index < tabs.size()) {
        if (tabs[current_playlist_index].list_obj) {
            tabs[current_playlist_index].list_obj->update_song_buttons_y(wheel_move);
        }
    }
}

void play_list_controller::draw_all() {
    if (current_playlist_index > 0 && current_playlist_index < tabs.size()) {
        if (tabs[current_playlist_index].list_obj) {
            tabs[current_playlist_index].list_obj->draw();
        }
    }
    if (bg_button) bg_button->drawButton();
    HRGN hRgn = CreateRectRgn(ctrl_x, ctrl_y, ctrl_x + ctrl_w, ctrl_y + ctrl_h);
    setcliprgn(hRgn);
    for (auto &t : tabs) {
        t.tab_button->drawButton();
    }
    setcliprgn(NULL);
    DeleteObject(hRgn);
}

std::string play_list_controller::get_current_song_path(int current_song_index) {
    if (current_playlist_index > 0 && current_playlist_index < tabs.size()) {
        if (tabs[current_playlist_index].list_obj) {
            return tabs[current_playlist_index].list_obj->get_song_address(current_song_index);
        }
    }
    return "";
}

bool play_list_controller::is_mouse_in_list_area(int x, int y) const {
    return (x >= ctrl_x && x <= ctrl_x + ctrl_w && y >= ctrl_y && y <= ctrl_y + 520 + 40);
}