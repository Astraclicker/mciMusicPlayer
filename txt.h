/*
*文本类
 *为其他函数或对象提供文本数据
 */
#pragma once
#include <string>
class txt {
public:
    int t_length;
    int t_width;
    int t_color;
    std::string Font_name;
    txt(int t_length,int t_width,int t_color,std::string Font_name);
};
