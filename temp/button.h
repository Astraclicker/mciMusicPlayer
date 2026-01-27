#pragma once
#include <graphics.h>
#include <iostream>
#include <string>

using namespace std;
/*
 * 自定义按钮类
 * 包含位置，大小，颜色，文字属性
 */
class Button {
private:
    int x,y;//左上角坐标
    int width,height;//按钮宽度/高度
    COLORREF color;//颜色
    string text;//按钮内容
    IMAGE img;
    bool isimage;
public:
    //文字按钮
    Button (int _x,int _y,int _width,int _height,COLORREF _color,string _text);
    //图片按钮
    Button(int _x,int _y,int _width,int _height,COLORREF _color,const char * imagePath);
    //绘制按钮
    void Draw();
    //判断点击
    bool IsClicked();
    //点击效果
    void ClickVision();
};