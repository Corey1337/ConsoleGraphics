#include "VideoToAscii.h"
#include "SFML/Audio.hpp"
#include <Windows.h>

VideoConverter::VideoConverter(const cv::VideoCapture& video)
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

void VideoConverter::converter(short fontSize)
{
    for (int i = 0;; i++)
    {
        std::cout << "Converting frames to ascii: " << i << "/" << framesCount;
        capture >> frame;
        if (frame.empty())
            break;
        asciiConverter.setImage(frame);
        asciiConverter.converter(fontSize);
        resolution = asciiConverter.getResolution();
        asciiFrames.push_back((std::string)asciiConverter.asciiOut(false, false));
        Screen::gotoZero();
        Screen::clearScreen();
    }
    std::cout << std::endl << "success" << std::endl;
}

void VideoConverter::asciiOut(bool consoleOut, bool txtOut)
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

        sf::SoundBuffer buffer;
        sf::Sound sound{buffer};

        bool isSoundLoaded = buffer.loadFromFile("sound.wav");
        if (!isSoundLoaded)
            std::cout << "Error: unable to load sound";

        Screen::clearScreen();
        Screen::setWindow(resolution.x, resolution.y);

        using std::chrono::duration_cast;
        using std::chrono::high_resolution_clock;
        using std::chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        auto t2 = high_resolution_clock::now();

        if (isSoundLoaded)
        {
            sound.setBuffer(buffer);
            sound.play();
        }


        HANDLE hConsole = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            0,
            nullptr,
            CONSOLE_TEXTMODE_BUFFER,
            nullptr);

        SetConsoleActiveScreenBuffer(hConsole);
        DWORD dwBytesWritten = 0;

        auto msInt = duration_cast<milliseconds>(t2 - t1);
        while (msInt.count() < durationMS)
        {
            WriteConsoleOutputCharacter(
                hConsole,
                (LPCSTR)asciiFrames[framesCount * msInt.count() / durationMS].data(),
                resolution.x * resolution.y,
                {0, 0},
                &dwBytesWritten);

            msInt = duration_cast<milliseconds>(high_resolution_clock::now() - t1);
        }
        auto seq = L"\x1b[2J";
        WriteConsoleW(hConsole, seq, (DWORD)wcslen(seq), &dwBytesWritten, nullptr);
        Screen::clearScreen();
        std::remove("sound.wav");
    }
}