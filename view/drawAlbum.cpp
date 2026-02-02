#include "drawAlbum.h"
#include <easyx.h>
#include "drawPlayList.h"


void drawAlbum (int index) {
    //??????
    if (my_play_list_controller.get_current_playlist_size() == 0) {
         return;
    }
    if (index<0||index>my_play_list_controller.get_current_playlist_size()) {
        return;
    }
    std::string CurrentPath = music_path +"/"+my_play_list_controller.get_current_song_name() + ".jpg";
    //std::string CurrentPath = music_path + "?????????" + ".jpg";
    IMAGE cover_img;
    loadimage(&cover_img, CurrentPath.c_str(), width_album, length_album);
    putimage(41, 114, &cover_img);
}