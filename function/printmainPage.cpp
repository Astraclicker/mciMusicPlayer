//
// Created by ray51 on 2026/1/28.
//
// #include "app_loop.h"
// #include <graphics.h>
// #include <iostream>
//
// // 定义全局变量（如果尚未在其他文件中定义）
// statu condition = statu::main;
// button_img button_setting(30, 30, 40, 100, "sources/image/files_ui/btn_settings_down.png");
// button_img button_pause(490, 650, 40, 100, "sources/image/control/btn_pause_down.png");
// button_txt button_spectrum(200, 150, 120, 40, 0xb79724, button_style::roundrect,
//                           "频谱图", 0x000000, "宋体");
//
// // 主循环函数
// void runAppLoop() {
//     while (true) {
//         if (condition == statu::main) {
//             handleMainInterface();
//         } else if (condition == statu::setting) {
//             handleSettingInterface();
//         }
//     }
// }
//
// // 处理主界面
// void handleMainInterface() {
//     drawMain();  // 假设 drawMain() 在其他地方定义
//
//     ExMessage mouse;
//     if (peekmessage(&mouse, EX_MOUSE)) {
//         if (mouse.message == WM_LBUTTONDOWN && button_setting.checkButton(mouse.x, mouse.y)) {
//             condition = statu::setting;
//         }
//         if (mouse.message == WM_LBUTTONDOWN && button_pause.checkButton(mouse.x, mouse.y)) {
//             condition = statu::main;
//         }
//     }
//     flushmessage();
// }
//
// // 处理设置界面
// void handleSettingInterface() {
//     drawSetting();  // 假设 drawSetting() 在其他地方定义
//
//     ExMessage Key;
//     if (peekmessage(&Key, EX_KEY)) {
//         if (Key.message == WM_KEYDOWN && Key.vkcode == VK_ESCAPE) {
//             condition = statu::main;
//         }
//     }
//
//     ExMessage mouse;
//     if (peekmessage(&mouse, EX_MOUSE)) {
//         if (mouse.message == WM_LBUTTONDOWN && button_spectrum.checkButton(mouse.x, mouse.y)) {
//             condition = statu::setting;
//             system("start sources/cava/cava.exe");
//             std::cout << "1" << std::endl;
//         }
//     }
//     flushmessage();
// }