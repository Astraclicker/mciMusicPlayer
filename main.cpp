//引用头文件时，只能应用归档的头文件，即除了temp文件夹下的文件，具体看CMakeLists.txt
#include "service/button.h"
#include <easyx.h>
int main() {
    initgraph(width_window,length_window);

    button base (50,100,RED,button_style::roundrect);
    button_color button1(50,50,base);
    button1.drawButton();
    while (true);
}