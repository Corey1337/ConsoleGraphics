#include <iostream>
#include "stdlib.h"
#include "VideoToAscii.h"
#include "area.h"
#include "Menu.h"


void ImgToAscii()
{
    std::string imgName;
    std::cout << "Image name or full path: ";
    std::cin >> imgName;

    int fontSize;
    std::cout << "Set font size: ";
    std::cin >> fontSize;
    std::cout << std::endl;

	cv::Mat imgCV;
    imgCV = cv::imread(imgName, cv::IMREAD_COLOR);

	if (imgCV.empty())
	{
		std::cout << "Could not read the image: " << imgName << std::endl;
	}
    else
    {
        AsciiConvert *conv = new AsciiConvert(imgCV);
        conv->converter(fontSize);
        conv->asciiOut();
        getchar();
        getchar();
        delete conv;
    }
}

void VideoToAscii()
{
    std::string videoName;
    std::cout << "Video name or full path: ";
    std::cin >> videoName;
    std::cout << std::endl;

    int fontSize;
    std::cout << "Set font size: ";
    std::cin >> fontSize;
    std::cout << std::endl;


    cv::VideoCapture capture(videoName);

    if(!capture.isOpened())
        throw "Error when reading steam_avi";
    else
    {
        std::string audio_conv_command = "ffmpeg -i " + videoName + " -vn sound.wav"; //need to ffmpeg installed
        system(audio_conv_command.c_str());
        VideoConverter *conv = new VideoConverter(capture);
        conv->converter(fontSize);
        std::cout << "Press key to start" << std::endl;
        getchar();
        getchar();
        conv->ascii_out(true, false);
        getchar();
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
