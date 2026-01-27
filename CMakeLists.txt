set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}../)
cmake_minimum_required(VERSION 4.1)
project(mciMusicPlayer)

set(CMAKE_CXX_STANDARD 20)

add_executable(mciMusicPlayer main.cpp
        button.cpp
        button.h
        txt.cpp
        txt.h
        def.h
        drawAlpha.h
        MusicPlayer.cpp
        MusicManager.cpp
        Button.cpp
        UI.cpp
        Song.cpp
)

target_link_libraries(mciMusicPlayer libeasyx.a)