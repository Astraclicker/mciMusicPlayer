#include "drawDeveloper.h"
void drawDeveloper() {
    BeginBatchDraw();
    developer.drawButton();
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 12, "FZCuYuan-M03");
    outtextxy(width_window/8 +20,length_window/8+40,"项目负责人：小林·牧之原稀音");
    outtextxy(width_window/8 +20,length_window/8+80,"架构设计：火豆，my，小林·牧之原稀音");
    outtextxy(width_window/8 +20,length_window/8+120,"核心功能：现实的延续，凉雨，111，my，叁拾，火豆，小林·牧之原稀音");
    FlushBatchDraw();
    EndBatchDraw();
}