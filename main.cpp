#include "start.h"
#include "view/drewSetting.h"
int main() {

    //声明音乐路径
    std::string music_address =music_path+"ちっちゃな私.mp3";

    //声明打开命令
    std::string open_command = "open \"" + music_address + "\" alias " + deviceName;

    //打开音乐文件
    mciSendString(open_command.c_str(), NULL, 0, NULL);

    //声明播放命令（只要在音乐路径前加一个play 就行注意，注意，注意，这里的play后有一个空格，一定要加！！！）
    std::string play_command = "play "+deviceName + " repeat";//后面可以加上repeat等状态

    //播放音乐
    mciSendString(play_command.c_str(),NULL,0,NULL);

    start();
    return 0;
}
