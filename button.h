
/*
 *按钮类
 *提供了三种形式的按钮
 *内部填充颜色的按钮
 *内部填充文字，背景为颜色的按钮
 *内部填充图片的按钮
 *提供了检测坐标是否存在于按钮内的函数
 *提供了分别画出三种按钮的函数
 */
#pragma once
#include "txt.h"
#include "def.h"
//按钮基类
class button {
protected:
    int length;
    int width;
    int color;
    button_style b_style;
public:
    button(int length,int width,int color,button_style b_style);
};
//内部填充颜色的按钮
class button_color : public button {
protected:
    int x;
    int y;
public:
    button_color(int x,int y,int length,int width,int color,button_style b_style);
    button_color(int x,int y,const button & b_obj);
    void drawButton();
    bool checkButton(int x,int y);
};
//内部填充文字，背景为颜色的按钮
class button_txt : public button {
protected:
    int x;
    int y;
    std::string text;
    int t_length;
    int t_width;
    int t_color;
    std::string Font_name;
public:
    button_txt(int x,int y,std::string text,int length,int width,int color,button_style b_style,const txt &obj);
    button_txt(int x,int y,std::string text,const button & b_obj,const txt &t_obj);
    void drawButton();
    bool checkButton(int x,int y);
};
//内部填充图片的按钮
class button_img :public button{
protected:
    int x;
    int y;
    std::string img_address;
public:
    button_img(int x,int y,int length,int width,int color,button_style b_style,std::string img_address);
    button_img(int x,int y,const button & b_obj,std::string img_address);
    void drawButton();
    bool checkButton(int x,int y);
};










