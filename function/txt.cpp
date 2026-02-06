#include "txt.h"

txt::txt(int t_length, int t_width, int t_color, std::string Font_name) {
    this->t_length = t_length;
    this->t_width = t_width;
    this->t_color = t_color;
    this->Font_name = Font_name;
}

int find_frist(const std::string str, int i) {
    int x = i;
    for (i; i < str.length(); i++) {
        if (str[i] == ' ') {
            return i;
        }
    }
    return x;
}
