#include <iostream>
#include "VideoToAscii.h"
#include "ImgToAsciiConverter.h"
#include "area.h"
#include "Menu.h"


void ImgToAscii()
{
    std::string imgName;
    std::cout << "Image name or full path: ";
    std::cin >> imgName;

	if (sf::Image image; image.loadFromFile(imgName) == false) {
		std::cout << "Could not read the image: " << imgName << std::endl;
	} else {
		short fontSize;
		std::cout << "Set font size: ";
		std::cin >> fontSize;
		std::cout << std::endl;

		auto *asciiConvert = new AsciiConvert(image);
		asciiConvert->converter(fontSize);
		asciiConvert->asciiOut();
		getchar();
		getchar();
		delete asciiConvert;
	}
}

void VideoToAscii()
{
    std::string videoName;
    std::cout << "Video name or full path: ";
    std::cin >> videoName;
    std::cout << std::endl;

    short fontSize;
    std::cout << "Set font size: ";
    std::cin >> fontSize;
    std::cout << std::endl;


    cv::VideoCapture capture(videoName);

    if(!capture.isOpened()) {
	    throw "Error when reading steam_avi";
    }

    std::string audio_conv_command = "ffmpeg -i " + videoName + " -vn sound.wav"; //need to ffmpeg installed
    system(audio_conv_command.c_str());
    auto *videoConvert = new VideoConverter(capture);
    videoConvert->converter(fontSize);
    std::cout << "Press key to start" << std::endl;
    getchar();
    getchar();
    videoConvert->asciiOut(true, false);
    getchar();
    delete videoConvert;
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

    menu.add_row(" 3. Animated Ball", [&](){ AnimatedBall(); });

    menu.add_row("Exit", nullptr);

    menu.run();
    return 0;
}