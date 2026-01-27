#include <easyx.h>
#include "button.h"
int main() {
    //提供了width_window和length_window为窗口提供参数
    initgraph(width_window,length_window);

    //构造字体类时提供四个参数，单个字的长/宽（若填写0，会自动处理），字颜色，字体
    txt CN(0,0,RED,"黑体");
    txt EN(0,0,RED,"JetBrainsMono Nerd Font");

    //创建基础按钮类，用于初始化后面更多的按钮,提供四个参数，按钮的长/宽，颜色，按钮形状
    button base(50,100,BLUE,button_style::roundrect);

    //创建文本按钮，提供5个参数，按钮的x，y坐标，按钮内文本，基础按钮类，字体样式类
    button_txt button1(50,50,"Hello World",base,CN);

    button1.drawButton();//用这个函数画出来
    while (true);
}