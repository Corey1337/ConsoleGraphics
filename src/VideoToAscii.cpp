#include "VideoToAscii.h"
#include "SFML/Audio.hpp"

VideoConverter::VideoConverter(cv::VideoCapture video)
{
    capture = video;
    fps = capture.get(cv::CAP_PROP_FPS);
    frames_Count = capture.get(cv::CAP_PROP_FRAME_COUNT);
    duration_ms = frames_Count / fps * 1000;
}

VideoConverter::~VideoConverter()
{
    screen.reset();
}

void VideoConverter::converter()
{
    for (;;)
    {
        capture >> frame;
        if (frame.empty())
            break;
        ascii_converter.set_img(frame);
        ascii_converter.converter();
        Resolution = ascii_converter.getResolution();
        ascii_frames.push_back((std::string)ascii_converter.ascii_out(false, false));
    }
    std::cout << "success" << std::endl;
}

void VideoConverter::ascii_out()
{
    sf::Sound sound;
    sf::SoundBuffer buffer;
    bool is_Sound_Loaded = buffer.loadFromFile("sound.wav");
    if (!is_Sound_Loaded)
        std::cout << "Error: unable to load sound";
    
    screen.clearScreen();
    screen.SetFont(0, 3);
    screen.SetWindow(Resolution.x, Resolution.y);

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    if(is_Sound_Loaded)
    {
        sound.setBuffer(buffer);
        sound.play();
    }
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    while(ms_int.count() < duration_ms)
    {
        std::cout << (ascii_frames[frames_Count * ms_int.count() / duration_ms]);
        screen.gotoZero();
        screen.clearScreen();
        ms_int = duration_cast<milliseconds>(high_resolution_clock::now() - t1);
    }
}