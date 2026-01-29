//
// Created by Administrator on 2026/1/29.
//

#ifndef MCIMUSICPLAYER_MONTIOR_H
#define MCIMUSICPLAYER_MONTIOR_H
#include <iostream>
#include <vector>
#include <graphics.h>
class monitor{
private:
   //按钮组区域判断 、、最下面的播放按钮那一块

public:
    bool mouse();//鼠标操作后检测位置
    bool key();//键盘操作
    //实现对应功能
    void one_add();//添加音乐
    void one_add_he_list();//添加目录
    void one_start();//是否正在进行播放
    /**/
    void monitor_list();//是否操作播放列表中的音乐(双击)
    void one_list();//单击改变播放列表的显示(读入数据？) 、//有问题
    void monitor_comments();//是否操作弹幕
    void ont_log();//是否操作设置
    void one_end();//是否进行退出
    monitor();//监测用户操作
    bool monitor_list_end();//音乐是否播放停止

};
#endif //MCIMUSICPLAYER_MONTIOR_H