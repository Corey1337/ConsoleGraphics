#include <iostream>
#include "ImgToAsciiConverter.h"
#include "area.h"
#include "Menu.h"
#include <opencv2/opencv.hpp>


void ImgToAscii(const char* Img_Name)
{
	cv::Mat img_cv;
    img_cv = cv::imread(Img_Name, cv::IMREAD_COLOR);

	if (img_cv.empty())
	{
		std::cout << "Could not read the image: " << Img_Name << std::endl;
	}
    else
    {
        cv::Mat img_cv_tmp;
        cv::cvtColor(img_cv, img_cv_tmp, cv::COLOR_BGR2RGBA);

        AsciiConvert *conv = new AsciiConvert();
        conv->set_img(img_cv_tmp);
        conv->converter();
        conv->ascii_out(true, true);
        getchar();
        
        delete conv;

    }


}

void VideoToAscii(const char* Video_Name)
{
    // sfe::Movie movie;

    // if (!movie.openFromFile(Video_Name))
    // {
    //     std::cout << "failed to open movie";
    // }

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
        { ImgToAscii("aska.jpg"); });

    menu.add_row(
        " 2. Video to ascii", [&]()
        { VideoToAscii("5sec.mp4"); });

    menu.add_row(
        " 3. Animated Ball", [&]()
        { AnimatedBall(); });

    menu.add_row(
        "Exit", nullptr);

    menu.run();
    return 0;
}
