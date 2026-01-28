#pragma once
#include "button1.h"

inline button_color base_spectrum(50, 200, 40, 120, 0xb79724, button_style::roundrect);
//????????
inline button_txt button_spectrum(200, 150, 120, 40, 0xb79724, button_style::roundrect, "ÆµÆ×Í¼", 0x000000, "ËÎÌå");
void drawSetting () {
    setfillcolor(0x808080);
    BeginBatchDraw();
    fillroundrect(width_window/8,length_window/8,width_window-width_window/8,length_window-length_window/8,10,10);
    button_spectrum.drawButton();
    FlushBatchDraw();
    EndBatchDraw();
}