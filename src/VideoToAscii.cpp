#include "VideoToAscii.h"

VideoConverter::VideoConverter(cv::VideoCapture video)
{
    capture = video;
}

VideoConverter::~VideoConverter()
{
    screen.reset();
}

void VideoConverter::converter()
{
    for( ; ; )
    {
        capture >> frame;
        if(frame.empty())
            break;
        ascii_converter.set_img(frame);
        ascii_converter.converter();
        Resolution = ascii_converter.getResolution();
        ascii_frames.push_back(ascii_converter.ascii_out(false, false));
    }
    std::cout << "success";
}

void VideoConverter::ascii_out()
{
    screen.SetFont(0, 3);
	screen.SetWindow(Resolution.x, Resolution.y);
    // screen.fullScreen();
    for(int i = 0; i < ascii_frames.size(); i++)
    {
        std::cout << ascii_frames[i];
		screen.gotoZero();
		screen.clearScreen();
    }
}