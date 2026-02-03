/*
 * 功能：
 * 播放列表的核心控制器与绘制定义
 * 负责人：现实的延续
 */
#ifndef MCIMUSICPLAYER_DRAWPLAYLIST_H
#define MCIMUSICPLAYER_DRAWPLAYLIST_H

#include "../service/Song.h"
#include <vector>
#include <string>
#include "../function/button.h"


struct playlist_song {
    Song song;
    button_txt* playlist_button;
};

class playlist {
public:
    playlist();
    ~playlist();

    // 重载整个播放列表
    void reload(const std::vector<Song> &songs_list_data);

    // 添加播放列表
    void load(const std::vector<Song> &songs_list_data);

    // 添加歌曲到播放列表
    void add_song(const Song &song);

    // 交互逻辑
    void update_song_buttons_y(int wheel_move);

    // 检测是点击哪首歌曲
    // 并返回点击的歌曲索引
    // 如果没有点击到（中间的空白区域）则返回-1
    int is_click_button(int x, int y);

    // 根据传入的索引值从当前播放列表移除该歌曲
    void delete_song_from_current_playlist(int current_song_index);

    // 根据获取到的索引值，返回对应歌曲所在地址
    std::string get_song_address(int current_song_index);

    // 内部辅助函数，在类体里面实现默认为视作内联函数，方便在内部反复使用
    // 用于判断playlist_songs是否为空，如果为空，调用该函数的函数应执行相应保护措施避免程序崩溃
    bool is_empty() const { return playlist_songs.empty(); }

    // 绘制该播放列表
    void draw();

    // 获取当前歌曲的在全局歌单区域的index
    int get_songs_list_index(int clicked_song_index);

    int get_playlist_size(){return playlist_songs.size();}

    int get_song_time(int current_song_index){return playlist_songs[current_song_index].song.song_time;}
    std::string get_song_name(int current_song_index) const{return playlist_songs[current_song_index].song.song_name;}

    // 获取播放列表坐标的相关参数，方便点击范围的判定
    int get_bg_playlist_x() const { return bg_playlist_x; }
    int get_bg_playlist_y() const { return bg_playlist_y; }
    int get_bg_playlist_W() const { return bg_playlist_W; }
    int get_bg_playlist_H() const { return bg_playlist_H; }

private:
    // 播放列表背景按钮
    button_color* bg_button;
    // 播放列表按钮字体
    txt songFont;
    // 当前播放列表的歌曲容器
    std::vector<playlist_song> playlist_songs;

    // 播放列表位置信息
    int bg_playlist_x, bg_playlist_y;
    int bg_playlist_W, bg_playlist_H;
    // 歌曲按钮的高度和间隙
    int song_button_H, song_button_gap;
};

// ==========================================
// 播放列表总控制器 (负责管理多个标签页)
// ==========================================
struct PlaylistTab {

    // 标签按钮 (如"默认列表")
    button_txt* tab_button;

    // 对应的播放列表实体
    playlist* list_obj;
};

class play_list_controller {
public:
    play_list_controller();
    ~play_list_controller();

    // 安全地重载当前选中的列表数据
    // 适配当前的歌曲列表加载模式，可以直接重载整播放列表
    void reload_current_list(const std::vector<Song> &global_data);

    void load_current_list(const std::vector<Song> &global_data);

    // 将选中歌曲添加到当前播放列表
    // 若后续可以让用户直接添加指定歌曲，则在获取到相应歌曲信息后
    // 实例化一Song对象并直接调用该函数添加到当前播放列表
    void add_song_to_current_list(const Song& new_song) const;

    // 处理鼠标点击消息
    // 传入鼠标消息的x,y值
    // 在外部先判断是否为右键点击
    // 如果为左键点击传入false
    // 如果为右键点击传入true
    // 同时在内部判断是在上方的播放列表控制器区域，还是播放列表区域
    // 在播放列表内，双击鼠标左键或者右键返回歌曲索引
    // 如果为右键会执行delete_song_button从当前播放列表中移除该歌曲
    int handle_click(int x, int y, bool is_right_click = false);

    // 处理鼠标滚轮消息
    // 传入鼠标消息的x,y值与鼠标滚轮消息
    // 同时在内部判断是在上方的播放列表控制器区域，还是播放列表区域，并执行相应函数，进行操作
    void handle_wheel(int wheel_move, int mouse_x, int mouse_y);

    // 直接drawmain.h中调用该函数，可以直接绘制出播放列表和上方控制器
    void draw_all();

    // 根据得到的索引值返回歌曲路径
    std::string get_current_song_path(int current_song_index);

    // 内部辅助函数，在类体里面实现默认为视作内联函数，方便在内部反复使用
    // 用于获取当前播放列表的索引，方便对当前播放列表进行相应操作
    int get_current_tab_index() const { return current_playlist_index; }

    // 根据获取到的鼠标消息，判断是否在播放列表区的管辖内
    // 不属于则返回false，属于返回true
    // 在start.h中调用，实现判断
    bool is_mouse_in_list_area(int x, int y) const;

    int get_current_playlist_index() const { return current_playlist_index; }

    int get_current_playlist_size() const{return tabs[current_playlist_index].list_obj->get_playlist_size();}

    std::string get_current_song_name() const{return tabs[current_playlist_index].list_obj->get_song_name(current_song_index);}

    int get_current_song_time()const ;
private:
    // 添加播放列表
    void add_playlist_tab();

    // 删除播放列表
    void delete_playlist_tab(int index);

    // 根据点击到的播放列表控制器的索引
    // 通过修改当前播放列表的索引，实现播放列表的切换
    void switch_tab(int index);

    // 播放列表总控制器的容器
    std::vector<PlaylistTab> tabs;

    // 当前播放列表的索引
    int current_playlist_index;
    // 播放列表总控制器背景按钮
    button_color* bg_button;
    // 播放列表总控制器背景按钮的坐标和宽高
    int ctrl_x, ctrl_y, ctrl_w, ctrl_h;
    // 播放列表总控制器宽和高
    int tab_btn_w, tab_btn_h;
    // 播放列表总控制器按钮字体
    txt tabFont;
};


inline play_list_controller my_play_list_controller;

inline playlist defalt_playlist;

#endif