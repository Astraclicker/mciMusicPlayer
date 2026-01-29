/*
 * 优化后的按钮类头文件 (button.h)
 * 包含：button(基类), button_color, button_txt, button_img
 * 修复：在基类中添加 updateState 虚函数，支持多态调用
 */
#pragma once

#include <string>
#include <iostream>
#include <graphics.h>
#include "def.h" // 包含 button_style 枚举定义
#include "txt.h" // 包含文字处理相关类（根据您的项目结构保留）



// 按钮状态枚举：管理三种形态
enum class ButtonState {
    NORMAL, // 正常状态
    HOVER,  // 鼠标悬停
    DOWN    // 鼠标按下
};

// ===========================================================
// 按钮基类 (Base Class)
// ===========================================================
class button1 {
protected:
    int x;          // 坐标 X
    int y;          // 坐标 Y
    int length;     // 高度 (Height) - 注意：根据您的代码习惯，length用作垂直高度
    int width;      // 宽度 (Width)
    int color;      // 基础颜色
    button_style b_style; // 按钮样式 (圆角、矩形等)

    bool is_visible; // 控制按钮是否可见/可交互

public:
    // 构造函数
    button1(int x, int y, int length, int width, int color, button_style b_style);

    // 虚析构函数 (通过基类指针删除子类对象时防止内存泄漏)
    virtual ~button1() = default;

    // 纯虚函数：绘制逻辑由子类具体实现
    virtual void drawButton() = 0;

    // 虚函数：检测鼠标是否在按钮区域内 (默认矩形检测)
    virtual bool checkButton(int mouse_x, int mouse_y);

    // 【关键新增】状态更新虚函数
    // mouse_x, mouse_y: 鼠标位置
    // is_mouse_down: 鼠标左键是否按下
    // 返回值: true 表示状态发生改变(需要重绘)，false 表示无变化
    virtual bool updateState(int mouse_x, int mouse_y, bool is_mouse_down) {
        // 基类默认不做任何状态更新，返回 false
        return false;
    }

    // Setter / Getter
    void setPosition(int new_x, int new_y) { x = new_x; y = new_y; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setVisible(bool v) { is_visible = v; }
    bool getVisible() const { return is_visible; }
};

// ===========================================================
// 纯色按钮 (Color Button)
// ===========================================================
class button_color : public button1 {
public:
    // 继承基类构造函数
    using button1::button1;

    // 实现绘制函数
    void drawButton() override;
};

// ===========================================================
// 文字按钮 (Text Button)
// ===========================================================
class button_txt : public button1 {
protected:
    std::string text;       // 按钮文本
    int t_color;            // 文字颜色
    std::string font_name;  // 字体名称

public:
    // 构造函数
    // 注意：这里的参数 w 和 h 对应基类的 width 和 length
    button_txt(int x, int y, int w, int h, int color, button_style style,
               const std::string& text, int t_color, const std::string& font_name);

    // 实现绘制函数
    void drawButton() override;
};

// ===========================================================
// 图片按钮 (Image Button) - 核心交互组件
// ===========================================================
class button_img : public button1 {
protected:
    // 图片资源路径
    std::string img_norm;   // 常态图片
    std::string img_hover;  // 悬停图片
    std::string img_down;   // 按下图片
    std::string img_mask;   // 遮罩/掩码图片 (用于像素级碰撞)

    // 当前状态
    ButtonState current_state;

    // 内部辅助函数：检查掩码图对应位置是否透明
    bool checkMaskPixel(int local_x, int local_y);

public:
    // 全功能构造函数
    // norm: 必须提供
    // hover, down, mask: 可选，为空时有默认处理
    button_img(int x, int y, int length, int width,
               const std::string& norm,
               const std::string& hover = "",
               const std::string& down = "",
               const std::string& mask = "");

    // 实现绘制：根据状态画不同的图
    void drawButton() override;

    // 重写状态更新逻辑：实现 Norm -> Hover -> Down 的切换
    bool updateState(int mouse_x, int mouse_y, bool is_mouse_down) override;

    // 重写检测逻辑：支持像素级遮罩检测
    bool checkButton(int mouse_x, int mouse_y) override;
};


class Button {
private:
    int x,y;//左上角坐标
    int width,height;//按钮宽度/高度
    COLORREF color;//颜色
    std::string text;//按钮内容
    IMAGE img;
    bool isimage;
public:
    //文字按钮
    Button (int _x,int _y,int _width,int _height,COLORREF _color,std::string _text);
    //图片按钮
    Button(int _x,int _y,int _width,int _height,COLORREF _color,const char * imagePath);
    //绘制按钮
    void Draw();
    //判断点击
    bool IsClicked();
    //点击效果
    void ClickVision();
};