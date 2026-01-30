#include "drawPlayList.h"
#include "../service/Song.h"
#include "../function/button.h"
#include "easyx.h"

void draw_play_list(std::vector<Song> &songs_list) {
    std::vector<button_txt*> song_buttons;
    txt songFont(18, 0, 0x333333, "微软雅黑");

    int bg_playlist_x = 952;
    int bg_playlist_y = 164;
    int bg_playlist_W = 316;
    int bg_playlist_H = 465;
    int song_buttons_H = 40;

    int bg_playlist_color = 0xF5F5F5;

    button_color bg_playlist(
        bg_playlist_x,
        bg_playlist_y,
        bg_playlist_H,
        bg_playlist_W,
        bg_playlist_color,
        button_style::roundrect
    );
    int gap = 5;
    int padding = 10;

    bg_playlist.drawButton();

    for (size_t i = 0; i < songs_list.size(); ++i) {

        int currentY = bg_playlist_y + padding + static_cast<int>(i) * (song_buttons_H + gap);

        if (currentY + song_buttons_H > bg_playlist_y + bg_playlist_H) {
            break;
        }

        button_txt* song_button = new button_txt(
            bg_playlist_x + 8,
            currentY,
            songs_list[i].song_name,
            song_buttons_H,
            bg_playlist_W - 16,
            RGB(130, 185, 255),
            button_style::roundrect,
            songFont
        );

        song_buttons.push_back(song_button);
        song_button->drawButton();
    }
}
