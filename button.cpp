#include "Button.h"

Button::Button(int _x,int _y,int _width,int _height,COLORREF _color,string _text) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = _color;
    text = _text;
    isimage = false;
}
Button::Button(int _x,int _y,int _width,int _height,COLORREF _color,const char * imagePath) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = _color;
    isimage = true;
    loadimage(&img,imagePath,width,height);
}
void Button::Draw() {

}
bool Button::IsClicked() {

}
void Button::ClickVision() {

}