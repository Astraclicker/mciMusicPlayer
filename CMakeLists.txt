set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}../)
cmake_minimum_required(VERSION 4.1)
project(mciMusicPlayer)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SERVICE "service/*.cpp" "service/*.h")
file(GLOB_RECURSE FUNCTION "function/*.cpp" "function/*.h")
file(GLOB_RECURSE VIEW "view/*.cpp" "view/*.h")
#GLOB_RECURSE 根目录也能搜索
add_executable(mciMusicPlayer main.cpp
        ${SERVICE}
        ${FUNCTION}
        ${VIEW}
        start.h
        view/base.h
        view/drawPlayList.h
        view/drawPlayList.cpp
        service/loadfile.h
        service/loadfile.cpp
        service/Song.h
        function/playMusic.h
        function/playMusic.cpp
        view/drawPlayLine.cpp
        view/drawPlayLine.h
)

target_link_libraries(mciMusicPlayer libeasyx.a winmm.lib)