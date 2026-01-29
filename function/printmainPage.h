//
// Created by ray51 on 2026/1/28.
//

#ifndef MCIMUSICPLAYER_PRINTMAINPAGE_H
#define MCIMUSICPLAYER_PRINTMAINPAGE_H

// #include <iostream>
// #include <easyx.h>
//
// #include "def.h"
// #include "drawMain.h"
// #include "drewSetting.h"
//
//
// void drawSetting() {
//         while (true) {
//             if (condition == statu::main) {
//                 handleMainInterface();
//             } else if (condition == statu::setting) {
//                 handleSettingInterface();
//             }
//         }
//     }
//
//     void handleMainInterface() {
//         drawMain();
//         if (peekmessage(&mouse, EX_MOUSE)) {
//             if (mouse.message == WM_LBUTTONDOWN && button_setting.checkButton(mouse.x, mouse.y)) {
//                 condition = statu::setting;
//             }
//             if (mouse.message == WM_LBUTTONDOWN && button_pause.checkButton(mouse.x, mouse.y)) {
//                 condition = statu::main;
//             }
//         }
//         flushmessage();
//     }
//
//     void handleSettingInterface() {
//         drawSetting();
//         if (peekmessage(&Key, EX_KEY)) {
//             if (Key.message == WM_KEYDOWN && Key.vkcode == VK_ESCAPE) {
//                 condition = statu::main;
//             }
//         }
//         if (peekmessage(&mouse, EX_MOUSE)) {
//             if (mouse.message == WM_LBUTTONDOWN && button_spectrum.checkButton(mouse.x, mouse.y)) {
//                 condition = statu::setting;
//                 system("start sources/cava/cava.exe");
//                 std::cout << "1" << std::endl;
//             }
//         }
//         flushmessage();
//     }
//
//
// void printPage() {
//         drawSetting();
//         handleMainInterface();
//         handleSettingInterface();
//     }
//
//
//
//




#endif //MCIMUSICPLAYER_PRINTMAINPAGE_H