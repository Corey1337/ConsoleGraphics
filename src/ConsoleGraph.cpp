#include <iostream>
#include "stdlib.h"
#include "VideoToAscii.h"
#include "area.h"
#include "Menu.h"


void ImgToAscii()
{
    std::string img_name;
    std::cout << "Image name or full path: ";
    std::cin >> img_name;

	cv::Mat img_cv;
    img_cv = cv::imread(img_name, cv::IMREAD_COLOR);

	if (img_cv.empty())
	{
		std::cout << "Could not read the image: " << img_name << std::endl;
	}
    else
    {
        AsciiConvert *conv = new AsciiConvert(img_cv);
        conv->converter();
        conv->ascii_out();
        getchar();
        getchar();
        delete conv;
    }
}

void VideoToAscii()
{
    std::string video_name;
    std::cout << "Video name or full path: ";
    std::cin >> video_name;

    cv::VideoCapture capture(video_name);

    if(!capture.isOpened())
        throw "Error when reading steam_avi";
    else
    {
        std::string audio_conv_command = "ffmpeg -i " + video_name + " -vn sound.wav"; //need to ffmpeg installed
        system(audio_conv_command.c_str());
        VideoConverter *conv = new VideoConverter(capture);
        conv->converter();
        std::cout << "Press key to start" << std::endl;
        getchar();
        getchar();
        conv->ascii_out();
        delete conv;
    }
}

void AnimatedBall()
{
    Area area(120, 30);
    area.fill();
    getchar();
}

int main()
{
    Menu menu("Menu: ");

    menu.add_row(
        " 1. Img to ascii", [&]()
        { ImgToAscii(); });

    menu.add_row(
        " 2. Video to ascii", [&]()
        { VideoToAscii(); });

    menu.add_row(
        " 3. Animated Ball", [&]()
        { AnimatedBall(); });

    menu.add_row(
        "Exit", nullptr);

    menu.run();
    return 0;
}
