#include "VideoToAscii.h"
#include "SFML/Audio.hpp"
#include <Windows.h>

VideoConverter::VideoConverter(cv::VideoCapture video)
{
    capture = video;
    fps = capture.get(cv::CAP_PROP_FPS);
    framesCount = capture.get(cv::CAP_PROP_FRAME_COUNT);
    durationMS = framesCount / fps * 1000;
}

VideoConverter::~VideoConverter()
{
    screen.reset();
}

void VideoConverter::converter(int fontSize)
{
    for (int i = 0;; i++)
    {
        std::cout << "Converting frames to ascii: " << i << "/" << framesCount;
        capture >> frame;
        if (frame.empty())
            break;
        asciiConverter.setImg(frame);
        asciiConverter.converter(fontSize);
        Resolution = asciiConverter.getResolution();
        asciiFrames.push_back((std::string)asciiConverter.asciiOut(false, false));
        screen.gotoZero();
        screen.clearScreen();
    }
    std::cout << std::endl << "success" << std::endl;
}

void VideoConverter::ascii_out(bool consoleOut, bool txtOut)
{
    if (txtOut)
    {
        std::ofstream txtresult;
        txtresult.open("ascii.txt");
        for (int i = 0; i < asciiFrames.size(); i++)
        {
            txtresult << asciiFrames[i];
        }
        txtresult.close();
    }

    if (consoleOut)
    {
        std::ios_base::sync_with_stdio(false);

        sf::Sound sound;
        sf::SoundBuffer buffer;
        bool is_Sound_Loaded = buffer.loadFromFile("sound.wav");
        if (!is_Sound_Loaded)
            std::cout << "Error: unable to load sound";

        screen.clearScreen();
        screen.setWindow(Resolution.x, Resolution.y);

        using std::chrono::duration_cast;
        using std::chrono::high_resolution_clock;
        using std::chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        auto t2 = high_resolution_clock::now();

        if (is_Sound_Loaded)
        {
            sound.setBuffer(buffer);
            sound.play();
        }


        HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(hConsole);
        DWORD dwBytesWritten = 0;

        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        while (ms_int.count() < durationMS)
        {
            WriteConsoleOutputCharacter(hConsole, (LPCSTR)asciiFrames[framesCount * ms_int.count() / durationMS].data(), Resolution.x * Resolution.y, {0, 0}, &dwBytesWritten);

            ms_int = duration_cast<milliseconds>(high_resolution_clock::now() - t1);
        }
        auto seq = L"\x1b[2J";
        WriteConsoleW(hConsole, seq, (DWORD)wcslen(seq), &dwBytesWritten, NULL);
        screen.clearScreen();
        std::remove("sound.wav");
    }
}