/*
 * 按钮类具体实现 (.cpp)
 * 对应头文件: button_optimized.h
 * 依赖: EasyX (graphics.h), drawAlpha.h
 * 实现逻辑：
 * 1. 构造函数使用初始化列表，高效赋值。
 * 2. button_img 实现了状态机逻辑 (updateState) 和像素级碰撞 (checkMaskPixel)。
 * 3. 兼容了 EasyX 的绘图函数。
 */

#include "button1.h"
#include <graphics.h>  // EasyX 图形库
#include "../function/drawAlpha.h" // 您的透明绘图工具
#include <iostream>

// ===========================================================
// button (基类) 实现
// ===========================================================

// 构造函数
button1::button1(int x, int y, int length, int width, int color, button_style b_style)
    : x(x), y(y), length(length), width(width), color(color), b_style(b_style), is_visible(true) {
    // 基础属性初始化完成
}

// 通用的矩形区域检测 (AABB)
bool button1::checkButton(int mouse_x, int mouse_y) {
    // 如果按钮不可见，直接返回 false
    if (!is_visible) return false;

    // 判断鼠标是否在矩形范围内
    // 注意：根据您的习惯，width 是水平宽度，length 是垂直高度
    return (mouse_x >= x && mouse_x <= x + width &&
            mouse_y >= y && mouse_y <= y + length);
}

// ===========================================================
// button_color (纯色按钮) 实现
// ===========================================================

// 绘制函数
void button_color::drawButton() {
    if (!is_visible) return;

    setfillcolor(color);
    // 这里可以设置无边框，或者根据 style 设置边框颜色
    // setlinecolor(BLACK); 

    switch (b_style) {
    case button_style::roundrect:
        // 圆角矩形，圆角大小设为 10, 10
        fillroundrect(x, y, x + width, y + length, 10, 10);
        break;
    case button_style::ellipse:
        // 椭圆
        fillellipse(x, y, x + width, y + length);
        break;
    default:
        // 默认画矩形
        fillrectangle(x, y, x + width, y + length);
        break;
    }
}

// ===========================================================
// button_txt (文字按钮) 实现
// ===========================================================

// 构造函数：使用初始化列表优化字符串
button_txt::button_txt(int x, int y, int w, int h, int color, button_style style,
                       const std::string& text, int t_color, const std::string& font_name)
    : button1(x, y, h, w, color, style), // 注意：基类构造参数顺序是 length(高), width(宽)，需根据您的定义对应
      text(text), t_color(t_color), font_name(font_name) {
}

// 绘制函数
void button_txt::drawButton() {
    if (!is_visible) return;

    // 1. 先画背景 (复用 button_color 的逻辑，或者直接重写)
    setfillcolor(color);
    switch (b_style) {
    case button_style::roundrect: fillroundrect(x, y, x + width, y + length, 10, 10); break;
    case button_style::ellipse:   fillellipse(x, y, x + width, y + length); break;
    default:                      fillrectangle(x, y, x + width, y + length); break;
    }

    // 2. 准备画文字
    RECT r = { x, y, x + width, y + length };
    setbkmode(TRANSPARENT); // 文字背景透明
    settextcolor(t_color);

    // 自动计算字体大小逻辑 (复用您原来的逻辑)
    // 注意：这里建议将 font_size 存为成员变量，避免每次 draw 都计算
    int t_w = 0, t_h = 0;
    if (text.length() > 0) {
        t_w = width / static_cast<int>(text.size()); // 粗略计算
        t_h = t_w * 2; // 假设高宽比
        // 限制最大高度，防止撑爆按钮
        if (t_h > length) t_h = length - 4; 
    }
    
    // 设置字体
    settextstyle(t_h, 0, font_name.c_str()); // 第二个参数0表示自适应宽度

    // 居中绘制
    drawtext(text.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// ===========================================================
// button_img (图片按钮) 实现 —— 核心部分！
// ===========================================================

// 全能构造函数
button_img::button_img(int x, int y, int length, int width,
                       const std::string& norm,
                       const std::string& hover,
                       const std::string& down,
                       const std::string& mask)
    : button1(x, y, length, width, 0, button_style::roundrect), // 图片按钮通常不需要背景色，给0
      img_norm(norm), img_hover(hover), img_down(down), img_mask(mask),
      current_state(ButtonState::NORMAL) 
{
    // 如果 hover 或 down 为空，默认让它们等于 norm
    // 这样如果没有悬停图，就不会显示空白，而是显示常态图
    if (img_hover.empty()) img_hover = img_norm;
    if (img_down.empty())  img_down = img_norm;
}

// 绘制函数：根据 current_state 选择图片
void button_img::drawButton() {
    if (!is_visible) return;

    std::string target_img_path;

    // 状态机分发
    switch (current_state) {
    case ButtonState::NORMAL: target_img_path = img_norm; break;
    case ButtonState::HOVER:  target_img_path = img_hover; break;
    case ButtonState::DOWN:   target_img_path = img_down; break;
    }

    if (target_img_path.empty()) return;

    // 【重要提示】：实时 loadimage 效率较低，仅为匹配当前头文件结构。
    // 建议：未来在类成员中直接存储 IMAGE 对象，在构造函数中加载。
    IMAGE temp_img;
    loadimage(&temp_img, target_img_path.c_str(), width, length, true);
    
    // 使用您的 drawAlpha 绘制透明图
    drawAlpha(x, y, &temp_img);
}

// 状态更新逻辑 (请在游戏主循环 Update 中调用)
bool button_img::updateState(int mouse_x, int mouse_y, bool is_mouse_down) {
    if (!is_visible) return false;

    ButtonState old_state = current_state;

    // 1. 先检测是否碰撞
    if (checkButton(mouse_x, mouse_y)) {
        // 2. 如果碰到了，判断是按下还是悬停
        if (is_mouse_down) {
            current_state = ButtonState::DOWN;
        } else {
            current_state = ButtonState::HOVER;
        }
    } else {
        // 3. 没碰到，恢复正常
        current_state = ButtonState::NORMAL;
    }

    // 返回 true 表示状态变了，通知外部重绘
    return (old_state != current_state);
}

// 像素级掩码检测辅助函数
bool button_img::checkMaskPixel(int local_x, int local_y) {
    if (img_mask.empty()) return true; // 没有掩码图，默认视为实心

    // 加载掩码图
    IMAGE temp_mask;
    loadimage(&temp_mask, img_mask.c_str(), width, length, true);

    // 获取掩码图的像素
    // 注意：EasyX 获取 Image 对象像素需要 SetWorkingImage
    SetWorkingImage(&temp_mask);
    COLORREF c = getpixel(local_x, local_y);
    SetWorkingImage(NULL); // 恢复绘图目标为窗口

    // 假设掩码图逻辑：黑色(0)为透明/不可点，其他颜色为可点
    // 您可以根据自己的掩码图制作规则修改这个判断
    return (c != BLACK); 
}

// 重写检测函数：加入 Mask 逻辑
bool button_img::checkButton(int mouse_x, int mouse_y) {
    // 1. 粗略检测：如果连矩形框都没进，肯定没点中
    // 直接调用基类的检测，省性能
    if (!button1::checkButton(mouse_x, mouse_y)) {
        return false;
    }

    // 2. 精确检测：如果有掩码图，检查像素
    if (!img_mask.empty()) {
        int local_x = mouse_x - x;
        int local_y = mouse_y - y;
        return checkMaskPixel(local_x, local_y);
    }

    // 没有掩码图，既然通过了矩形检测，那就是点中了
    return true;
}