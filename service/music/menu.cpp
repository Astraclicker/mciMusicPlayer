/*
 *程序状态机
 */
#include "menu.h"
#include "../../function/def.h"
#include "../montior.h"

#include "../../function/button.h"
#include "../../view/drawMain.h"
#include "../../view/drewSetting.h"
//#include "../player.h"
using std::cout;
using std::endl;



void menu::show_list() {
    cout << "show_list" << endl;
}

menu::menu() {

    log();//在这里实现读取设置
    initgraph(width_window,length_window);
    condition = statu::main;
    drawMain();
    ExMessage mouse;
    //Player song;
    while (1) {

        switch (condition) {
            case statu::main:
                drawMain();
                getmessage(&mouse,EX_MOUSE);
                //设置按钮的点击检测
                if (mouse.message==WM_LBUTTONDOWN&&button_setting.checkButton(mouse.x,mouse.y)) {
                    exit(0);

                    condition = statu::setting;
                }//单击设置
                if (mouse.message==WM_LBUTTONDOWN&&button_pause.checkButton(mouse.x,mouse.y)) {
                   //song.play();
                    //播放当前音频
                }//单击播放

                if(mouse.message==WM_LBUTTONDOWN&&button_backward.checkButton(mouse.x,mouse.y)) {
                    //将歌曲进度回退15秒
                }//单击回退
                // if (mouse.message==WM_LBUTTONDOWN&&button_add.checkButton(mouse.x,mouse.y)) {
                //
                // }//添加文件
                // if (mouse.message==WM_LBUTTONDOWN&&button_add.checkButton(mouse.x,mouse.y)) {
                //
                // }//添加目录
                //是否操作播放列表中的音乐(双击)

                break;
            case statu::setting:
                drawSetting();
                break;
        }

    }
}


//这里是绘制主界面的功能实现
//加载UI及美术资源，使用PATH_CONTROL,PATH_MODE和PATH_UI获取图标
void loadingUI();
//to Do by you
void voiceCtrl();
//音量键的绘制，在liangyu/ui_liangyu部分实现
void btndraw();
//按钮的绘制，这个在button中实现

//获取文件配置,创建播放列表，具体在playlist中实现,包括歌曲地址，歌名,歌曲清单和索引控制
void getfile();
//鼠标获取歌曲的控制，如上一首下一首，播放暂停等,这个具体在liangyu/player中实现
void SongCtrl();


/*
 * 实现监测操作及跳转
 *  根据用户点击的返回值决定调用哪个部分
 */
monitor::monitor() {
    cout << "monitor" << endl;
}


/*
 * 实现歌曲播放的流程
 */
