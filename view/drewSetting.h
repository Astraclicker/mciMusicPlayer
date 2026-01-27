#pragma once
#include "../service/button.h"

inline button base_spectrum (50,200,0xb79724,button_style::roundrect);
//初始化按钮
inline button_txt button_spectrum(200,150,"开启频谱",base_spectrum,CN);
void drawSetting () {
    setfillcolor(0x808080);
    BeginBatchDraw();
    fillroundrect(width_window/8,length_window/8,width_window-width_window/8,length_window-length_window/8,10,10);
    button_spectrum.drawButton();
    FlushBatchDraw();
    EndBatchDraw();
}