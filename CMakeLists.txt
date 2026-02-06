set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}../)
cmake_minimum_required(VERSION 4.1)
project(mciMusicPlayer)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SERVICE "service/*.cpp" "service/*.h" "service/*.c")
file(GLOB_RECURSE FUNCTION "function/*.cpp" "function/*.h")
file(GLOB_RECURSE VIEW "view/*.cpp" "view/*.h")

add_executable(mciMusicPlayer main.cpp
        ${SERVICE}
        ${FUNCTION}
        ${VIEW}
)

target_link_libraries(mciMusicPlayer libeasyx.a winmm.lib)