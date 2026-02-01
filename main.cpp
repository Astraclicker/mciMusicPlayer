#include "start.h"
#include "view/drewSetting.h"

int main() {


// songs_list.push_back({11, "Stay With Me - 松原みき", "./music/Stay With Me.mp3", 0});
// songs_list.push_back({12, "光るなら - Goose house", "./music/光るなら.mp3", 0});
// songs_list.push_back({13, "七里香 - 周杰伦", "./music/七里香.mp3", 0});
// songs_list.push_back({14, "Shape of You - Ed Sheeran", "./music/Shape of You.mp3", 0});
// songs_list.push_back({15, "青鸟 - 生物股长", "./music/青鸟.mp3", 0});
// songs_list.push_back({16, "恋爱循环 - 花泽香菜", "./music/恋爱循环.mp3", 0});
// songs_list.push_back({17, "Butter-Fly - 和田光司", "./music/Butter-Fly.mp3", 0});
// songs_list.push_back({18, "红莲华 - LiSA", "./music/红莲华.mp3", 0});
// songs_list.push_back({19, "小幸运 - 田馥甄", "./music/小幸运.mp3", 0});
// songs_list.push_back({20, "演员 - 薛之谦", "./music/演员.mp3", 0});
// songs_list.push_back({21, "Counting Stars - OneRepublic", "./music/Counting Stars.mp3", 0});
// songs_list.push_back({22, "アイドル - YOASOBI", "./music/アイドル.mp3", 0});
// songs_list.push_back({23, "再一次 - 邓紫棋", "./music/再一次.mp3", 0});
// songs_list.push_back({24, "Something Just Like This - The Chainsmokers", "./music/Something Just Like This.mp3", 0});
// songs_list.push_back({25, "前前前世 - RADWIMPS", "./music/前前前世.mp3", 0});
// songs_list.push_back({26, "如果可以 - 韦礼安", "./music/如果可以.mp3", 0});
// songs_list.push_back({27, "Bad Guy - Billie Eilish", "./music/Bad Guy.mp3", 0});
// songs_list.push_back({28, "烟花易冷 - 周杰伦", "./music/烟花易冷.mp3", 0});
// songs_list.push_back({29, "红豆 - 王菲", "./music/红豆.mp3", 0});
// songs_list.push_back({30, "怪物 - YOASOBI", "./music/怪物.mp3", 0});
// songs_list.push_back({31, "想去海边 - 夏日入侵企画", "./music/想去海边.mp3", 0});
// songs_list.push_back({32, "Never Gonna Give You Up - Rick Astley", "./music/Never Gonna Give You Up.mp3", 0});
// songs_list.push_back({33, "一剪梅 - 费玉清", "./music/一剪梅.mp3", 0});
// songs_list.push_back({34, "First Love - 宇多田光", "./music/First Love.mp3", 0});
// songs_list.push_back({35, "这就是爱 - 张杰", "./music/这就是爱.mp3", 0});
// songs_list.push_back({36, "Blinding Lights - The Weeknd", "./music/Blinding Lights.mp3", 0});
// songs_list.push_back({37, "年少有为 - 李荣浩", "./music/年少有为.mp3", 0});
// songs_list.push_back({38, "逆战 - 张杰", "./music/逆战.mp3", 0});
// songs_list.push_back({39, "起风了 - 买辣椒也用券", "./music/起风了.mp3", 0});
// songs_list.push_back({40, "遇见 - 孙燕姿", "./music/遇见.mp3", 0});
    //声明音乐路径
    std::string music_address =music_path+"ちっちゃな私.mp3";

    //声明打开命令
    std::string open_command = "open \"" + music_address + "\" alias " + deviceName;

    //打开音乐文件
    mciSendString(open_command.c_str(), NULL, 0, NULL);

    // 声明播放命令（只要在音乐路径前加一个play 就行注意，注意，注意，这里的play后有一个空格，一定要加！！！）
    std::string play_command = "play "+deviceName + " repeat";//后面可以加上repeat等状态
    //
    // 播放音乐
    mciSendString(play_command.c_str(),NULL,0,NULL);

    start();
    return 0;
}
