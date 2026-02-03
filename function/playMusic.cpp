#include "playMusic.h"
#include <windows.h>
#include "../view/drawPlayList.h"
#include "../view/drewSetting.h"
#include "../view/drawLyrics.h"
//��ͣ/���ſؼ�
void control_music (playStatu&status) {
    if (status == playStatu::pause) {
        // ��ͣ -> ����
        mciSendString("play myaudio", NULL, 0, NULL);
        status = playStatu::play;
    }
    else { // status == PlayStatus::play
        // ���� -> ��ͣ
        mciSendString("stop myaudio", NULL, 0, NULL);
        status = playStatu::pause;
    }
}

void play_music (int newindex) {
    if (newindex < 0 || newindex >= my_play_list_controller.get_current_playlist_size()) return;
    current_song_index = newindex;
    // ֹͣ��ǰ����
    mciSendString("close myaudio", NULL, 0, NULL);

    // ���¸���
    std::string cmd = "open \"" + my_play_list_controller.get_current_song_path(current_song_index) + "\" alias myaudio";
    mciSendString(cmd.c_str(), NULL, 0, NULL);

    // ����
    mciSendString("play myaudio", NULL, 0, NULL);
    play_statu = playStatu::play;
    setVolume(volume);
    loadLyrics();
}

//������һ��/��һ��
void play_NextMusic() {
    switch (play_mode) {
        case PlayMode::Sequence:
            current_song_index = current_song_index + 1;
            if (current_song_index >= my_play_list_controller.get_current_playlist_size()) {
                current_song_index = 0;  // ѭ������һ��
            }
            break;
        case PlayMode::Sing_Loop:
            //index=index����
            break;
        case PlayMode::Random:
            current_song_index=rand() % my_play_list_controller.get_current_playlist_size() ;
            break;
    }
    play_music(current_song_index);
}

void play_PreviousMusic() {
    switch (play_mode) {
        case PlayMode::Sequence:
            current_song_index=current_song_index - 1;
            if (current_song_index < 0) {
                current_song_index = my_play_list_controller.get_current_playlist_size() - 1;  // ѭ�������һ��
            }
            break;
        case PlayMode::Sing_Loop:
            //index=index����
            break;
        case PlayMode::Random:
            current_song_index=rand() % my_play_list_controller.get_current_playlist_size() ;
            break;
    }
    play_music(current_song_index);
}

//���Ž����жϣ���һ���Զ�����
void checkAndPlayNext() {
    static bool wasPlaying = false;
    char status[256];

    mciSendString("status myaudio mode", status, sizeof(status), NULL);

    if (strcmp(status, "playing") == 0) {
        wasPlaying = true;
    }
    else if (strcmp(status, "stopped") == 0 && wasPlaying) {
        wasPlaying = false;
        play_NextMusic();
    }
}
//���/����
void fastForward(int milliseconds) {
    char cmd[256];
    char positionStr[64];

    // 1. ��ȡ��ǰλ��
    mciSendString("status myaudio position", positionStr, sizeof(positionStr), 0);
    long currentPos = atol(positionStr);

    // 2. ��ȡý���ܳ��ȣ���ֹ������Χ��
    long totalLength = my_play_list_controller.get_current_song_time();

    // 3. ������λ��
    long newPos = currentPos + milliseconds;
    if (newPos > totalLength) {
        newPos = totalLength; // �������ܳ���
    }

    // 4. ��ת����λ��
    sprintf(cmd, "seek myaudio to %ld", newPos);
    mciSendString(cmd, NULL, 0, NULL);

    // 5. ��������
    mciSendString("play myaudio", NULL, 0, NULL);
}
void fastBackward(int milliseconds) {
    char cmd[256];
    char positionStr[64];

    // 1. ��ȡ��ǰλ��
    mciSendString("status myaudio position", positionStr, sizeof(positionStr), 0);
    long currentPos = atol(positionStr);

    // 2. ������λ�ã���С��0��
    long newPos = currentPos - milliseconds;
    if (newPos < 0) {
        newPos = 0;
    }

    // 3. ��ת����λ��
    sprintf(cmd, "seek myaudio to %ld", newPos);
    mciSendString(cmd, NULL, 0, NULL);

    // 4. ��������
    mciSendString("play myaudio", NULL, 0, NULL);
}

//���׽�����
float getProgress() {
    char posStr[64];

    // ��ȡ��ǰλ��
    mciSendString("status myaudio position", posStr, sizeof(posStr), 0);
    long currentPos = atol(posStr);

    // ��ȡ�ܳ���
    long totalLen = my_play_list_controller.get_current_song_time();

    // �������
    if (totalLen > 0) {
        return (float)currentPos / totalLen;
    }
    return 0.0f;
}
void drawSimpleProgressBar(int x, int y, int width, int height, float progress) {
    // 1. ���Ʊ�������ɫ��
    setfillcolor(LIGHTGRAY);
    fillrectangle(x, y, x + width, y + height);

    // 2. ���ƽ��ȣ���ɫ��
    if (progress > 0) {
        int progressWidth = (int)(width * progress);
        setfillcolor(RGB(38, 120, 255));
        fillrectangle(x, y, x + progressWidth, y + height);
    }

    // 3. ���Ʊ߿�
    rectangle(x, y, x + width, y + height);
    // 4. ������קСԲȦ
    if (progress > 0) {
        int circleX = x + (int)(width * progress);
        int circleY = y + height / 2;
        int circleRadius = 12;  // �̶���С

        // ��Ȧ����ɫ�߿�
        setlinecolor(RGB(20, 70, 180));
        setfillcolor(WHITE);
        fillellipse(circleX - circleRadius, circleY - circleRadius,
                   circleX + circleRadius, circleY + circleRadius);
        setlinecolor(WHITE);
    }
}

void clickProgressBarToSeek(int mouseX) {
    // 1. ������λ�ö�Ӧ�Ľ��� (0.0 ~ 1.0)
    float progress = (float)mouseX / 1280.0f;
    if (progress < 0) progress = 0;
    if (progress > 1) progress = 1;

    // 2. ��ȡ��Ƶ�ܳ���
    long totalTime = my_play_list_controller.get_current_song_time();

    // 3. ����Ŀ��ʱ��
    long targetTime = (long)(totalTime * progress);

    // 4. ֱ����ת��һ�仰�㶨��
    char cmd[128];
    sprintf(cmd, "seek myaudio to %ld", targetTime);
    mciSendString(cmd, NULL, 0, NULL);

    // 5. ��������
    mciSendString("play myaudio", NULL, 0, NULL);
    play_statu=playStatu::play;
}

