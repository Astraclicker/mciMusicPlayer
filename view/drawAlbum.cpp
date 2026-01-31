#include "drawAlbum.h"
#include <easyx.h>

void drawAlbum (std::vector<Song> &songs_list,int index) {
    //°²È«¼ì²é
    if (songs_list.empty()) {
         return;
    }
    if (index<0||index>songs_list.size()) {
        return;
    }
    Song& CurrentSong = songs_list[index];
    std::string CurrentPath = music_path + CurrentSong.song_name + ".jpg";
    //std::string CurrentPath = music_path + "¤Á¤Ã¤Á¤ã¤ÊË½" + ".jpg";
    IMAGE cover_img;
    loadimage(&cover_img, CurrentPath.c_str(), width_album, length_album);
    putimage(41, 114, &cover_img);
}