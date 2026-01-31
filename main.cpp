#include "start.h"
#include "service/StoW.h"
#include "view/drewSetting.h"
int main() {

    //mci使用示例

    //声明音乐路径
    std::string music_address =music_path+"ちっちゃな私.mp3";
    std::string cmd = "open \"" + music_address + "\" alias " + deviceName;
    mciSendString(cmd.c_str(), NULL, 0, NULL);
    //声明播放命令（只要在音乐路径前加一个play 就行注意，注意，注意，这里的play后有一个空格，一定要加！！！）
    std::string play_command = "play "+deviceName;

    //用mciSendStringW()函数，第一个参数写StoW(播放命令).c_str()
    mciSendString(play_command.c_str(),NULL,0,NULL);

    start();
    return 0;
}
