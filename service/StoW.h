#ifndef MCIMUSICPLAYER_STOW_H
#define MCIMUSICPLAYER_STOW_H
#include <codecvt>
#include <locale>
#include <string>
//窄流转宽流
inline std::wstring StoW(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}
#endif