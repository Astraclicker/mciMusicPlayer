/*
 * ���ܣ�
 * �����б��ĺ��Ŀ���������ƶ���
 * �����ˣ���ʵ������
 */
#ifndef MCIMUSICPLAYER_DRAWPLAYLIST_H
#define MCIMUSICPLAYER_DRAWPLAYLIST_H

#include "../service/Song.h"
#include <vector>
#include <string>
#include "../function/button.h"
#include "../service/congfig.h"


struct playlist_song {
    Song song;
    button_txt* playlist_button;
};

class playlist {
public:
    playlist();
    ~playlist();

    friend bool save_config();
    friend bool load_config();

    // �������������б�
    void reload(const std::vector<Song> &songs_list_data);

    // ���Ӳ����б�
    void load(const std::vector<Song> &songs_list_data);

    // ���Ӹ����������б�
    void add_song(const Song &song);

    // �����߼�
    void update_song_buttons_y(int wheel_move);

    // ����ǵ�����׸���
    // �����ص���ĸ�������
    // ���û�е�������м�Ŀհ������򷵻�-1
    int is_click_button(int x, int y);

    // ���ݴ��������ֵ�ӵ�ǰ�����б��Ƴ��ø���
    void delete_song_from_current_playlist(int current_song_index);

    // ���ݻ�ȡ��������ֵ�����ض�Ӧ�������ڵ�ַ
    std::string get_song_address(int current_song_index);

    // �ڲ���������������������ʵ��Ĭ��Ϊ���������������������ڲ�����ʹ��
    // �����ж�playlist_songs�Ƿ�Ϊ�գ����Ϊ�գ����øú����ĺ���Ӧִ����Ӧ������ʩ����������
    bool is_empty() const { return playlist_songs.empty(); }

    // ���Ƹò����б�
    void draw();

    // ��ȡ��ǰ��������ȫ�ָ赥�����index
    int get_songs_list_index(int clicked_song_index);

    int get_playlist_size(){return playlist_songs.size();}

    int get_song_time(int current_song_index){return playlist_songs[current_song_index].song.song_time;}
    std::string get_song_name(int current_song_index) const {
        return playlist_songs[current_song_index].song.song_name;
    }
    std::string get_song_root(int current_song_index) const{return playlist_songs[current_song_index].song.song_root;}

    // ��ȡ�����б��������ز�������������Χ���ж�
    int get_bg_playlist_x() const { return bg_playlist_x; }
    int get_bg_playlist_y() const { return bg_playlist_y; }
    int get_bg_playlist_W() const { return bg_playlist_W; }
    int get_bg_playlist_H() const { return bg_playlist_H; }

private:
    // �����б�������ť
    button_color* bg_button;
    // �����б���ť����
    txt songFont;
    // ��ǰ�����б��ĸ�������
    std::vector<playlist_song> playlist_songs;

    // �����б�λ����Ϣ
    int bg_playlist_x, bg_playlist_y;
    int bg_playlist_W, bg_playlist_H;
    // ������ť�ĸ߶Ⱥͼ�϶
    int song_button_H, song_button_gap;
};

// ==========================================
// �����б��ܿ����� (������������ǩҳ)
// ==========================================
struct PlaylistTab {

    // ��ǩ��ť (��"Ĭ���б�")
    button_txt* tab_button;

    // ��Ӧ�Ĳ����б�ʵ��
    playlist* list_obj;
};

class play_list_controller {
public:
    play_list_controller();
    ~play_list_controller();

    friend bool save_config();
    friend bool load_config();

    // ��ȫ�����ص�ǰѡ�е��б�����
    // ���䵱ǰ�ĸ����б�����ģʽ������ֱ�������������б�
    void reload_current_list(const std::vector<Song> &global_data);

    void load_current_list(const std::vector<Song> &global_data);

    // ��ѡ�и������ӵ���ǰ�����б�
    // �������������û�ֱ������ָ�����������ڻ�ȡ����Ӧ������Ϣ��
    // ʵ����һSong����ֱ�ӵ��øú������ӵ���ǰ�����б�
    void add_song_to_current_list(const Song& new_song) const;

    // �����������Ϣ
    // ���������Ϣ��x,yֵ
    // ���ⲿ���ж��Ƿ�Ϊ�Ҽ����
    // ���Ϊ����������false
    // ���Ϊ�Ҽ��������true
    // ͬʱ���ڲ��ж������Ϸ��Ĳ����б����������򣬻��ǲ����б�����
    // �ڲ����б��ڣ�˫�������������Ҽ����ظ�������
    // ���Ϊ�Ҽ���ִ��delete_song_button�ӵ�ǰ�����б����Ƴ��ø���
    int handle_click(int x, int y, bool is_right_click = false);

    // ������������Ϣ
    // ���������Ϣ��x,yֵ����������Ϣ
    // ͬʱ���ڲ��ж������Ϸ��Ĳ����б����������򣬻��ǲ����б����򣬲�ִ����Ӧ���������в���
    void handle_wheel(int wheel_move, int mouse_x, int mouse_y);

    // ֱ��drawmain.h�е��øú���������ֱ�ӻ��Ƴ������б����Ϸ�������
    void draw_all();

    // ���ݵõ�������ֵ���ظ���·��
    std::string get_current_song_path(int current_song_index);

    // �ڲ���������������������ʵ��Ĭ��Ϊ���������������������ڲ�����ʹ��
    // ���ڻ�ȡ��ǰ�����б�������������Ե�ǰ�����б�������Ӧ����
    int get_current_tab_index() const { return current_playlist_index; }

    // ���ݻ�ȡ���������Ϣ���ж��Ƿ��ڲ����б����Ĺ�Ͻ��
    // �������򷵻�false�����ڷ���true
    // ��start.h�е��ã�ʵ���ж�
    bool is_mouse_in_list_area(int x, int y) const;

    int get_current_playlist_index() const { return current_playlist_index; }

    int get_current_playlist_size() const{return tabs[current_playlist_index].list_obj->get_playlist_size();}

    std::string get_current_song_name() const {
        if (tabs[current_playlist_index].list_obj->is_empty()) {
            return "";
        }
        return tabs[current_playlist_index].list_obj->get_song_name(current_song_index);
    }

    std::string get_current_song_root() const{return tabs[current_playlist_index].list_obj->get_song_root(current_song_index);};

    int get_current_song_time()const ;
private:
    // ���Ӳ����б�
    void add_playlist_tab();

    // ɾ�������б�
    void delete_playlist_tab(int index);

    void delete_playlist_tab_for_load_config(int index);

    // ���ݵ�����Ĳ����б�������������
    // ͨ���޸ĵ�ǰ�����б���������ʵ�ֲ����б����л�
    void switch_tab(int index);

    // �����б��ܿ�����������
    std::vector<PlaylistTab> tabs;

    // ��ǰ�����б�������
    int current_playlist_index;
    // �����б��ܿ�����������ť
    button_color* bg_button;
    // �����б��ܿ�����������ť������Ϳ���
    int ctrl_x, ctrl_y, ctrl_w, ctrl_h;
    // �����б��ܿ��������͸�
    int tab_btn_w, tab_btn_h;
    // �����б��ܿ�������ť����
    txt tabFont;
};


inline play_list_controller my_play_list_controller;

inline playlist defalt_playlist;

#endif