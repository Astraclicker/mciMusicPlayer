#include "button.h"
#include "drawAlpha.h"
#include <iostream>
//构造基本按钮(color)
button::button(int length, int width, int color, button_style b_style) {
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
}

//构造颜色按钮
button_color::button_color(int x, int y, int length, int width, int color, button_style b_style) : button(
    length, width, color, b_style) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
}

button_color::button_color(int x, int y, const button &b_obj) : button(b_obj) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
}

//画出颜色按钮
void button_color::drawButton() {
    setfillcolor(color);
    switch (b_style) {
        case button_style::roundrect: fillroundrect(x, y, x + width, y + length, 10, 10);
            break;
        case button_style::ellipse: fillellipse(x, y, x + width, y + length);
            break;
    }
}

//检测颜色按钮
bool button_color::checkButton(int x, int y) {
    if (x > this->x && x < this->x + this->width && y > this->y && y < this->y + this->length) {
        return true;
    }
    return false;
}

//构造文本按钮
button_txt::button_txt(int x, int y, std::string text, int length, int width, int color, button_style b_style,
                       const txt &obj) : button(length, width, color, b_style) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
    this->text = text;
    this->t_length = obj.t_length;
    this->t_width = obj.t_width;
    this->t_color = obj.t_color;
    this->Font_name = obj.Font_name;
}

button_txt::button_txt(int x, int y, std::string text, const button &b_obj, const txt &t_obj) : button(b_obj) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
    this->text = text;
    this->t_length = t_obj.t_length;
    this->t_width = t_obj.t_width;
    this->t_color = t_obj.t_color;
    this->Font_name = t_obj.Font_name;
}

//画出文本按钮
void button_txt::drawButton() {
    setfillcolor(color);
    switch (b_style) {
        case button_style::roundrect: fillroundrect(x, y, x + width, y + length, 10, 10);
            break;
        case button_style::ellipse: fillellipse(x, y, x + width, y + length);
            break;
    }
    RECT r = {x, y, x + width, y + length};
    setbkmode(TRANSPARENT);
    settextcolor(t_color);
    if (t_length==0||t_width==0) {
        t_width = width/static_cast<int>(text.size());
        t_length = t_width*2;

    }
    settextstyle(t_length, t_width, Font_name.c_str());
    drawtext(text.c_str(), &r,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//检测文本按钮
bool button_txt::checkButton(int x, int y) {
    if (x > this->x && x < this->x + this->width && y > this->y && y < this->y + this->length) {
        return true;
    }
    return false;
}


//构造图片按钮
button_img::button_img(int x, int y, int length, int width, int color, button_style b_style,
                       std::string img_address) : button(length, width, color, b_style) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
    this->img_address = img_address;
}

button_img::button_img(int x, int y, const button &b_obj, std::string img_address) : button(b_obj) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->color = color;
    this->b_style = b_style;
    this->img_address = img_address;
}

//画出图片按钮
void button_img::drawButton() {
    setfillcolor(color);
    switch (b_style) {
        case button_style::roundrect: fillroundrect(x, y, x + width, y + length, 10, 10);
            break;
        case button_style::ellipse: fillellipse(x, y, x + width, y + length);
            break;
    }
    IMAGE picture;
    loadimage(&picture, img_address.c_str(), width, length, true);
    drawAlpha(x, y, &picture);
}

//检测图片按钮
bool button_img::checkButton(int x, int y) {
    if (x > this->x && x < this->x + this->width && y > this->y && y < this->y + this->length) {
        return true;
    }
    return false;
}
