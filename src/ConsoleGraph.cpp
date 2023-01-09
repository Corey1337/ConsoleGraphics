#include <iostream>
#include "VideoToAscii.h"
#include "area.h"
#include "Menu.h"


void ImgToAscii(std::string Img_Name)
{
	cv::Mat img_cv;
    img_cv = cv::imread(Img_Name, cv::IMREAD_COLOR);

	if (img_cv.empty())
	{
		std::cout << "Could not read the image: " << Img_Name << std::endl;
	}
    else
    {
        AsciiConvert *conv = new AsciiConvert(img_cv);
        conv->converter();
        // conv->ascii_out(true, true);

        // using std::chrono::high_resolution_clock;
        // using std::chrono::duration_cast;
        // using std::chrono::duration;
        // using std::chrono::milliseconds;

        // auto t1 = high_resolution_clock::now();
        conv->ascii_out(true, false);
        // auto t2 = high_resolution_clock::now();
        getchar();
        
        delete conv;

        // auto ms_int = duration_cast<milliseconds>(t2 - t1);
        // duration<double, std::milli> ms_double = t2 - t1;

        // std::cout << ms_int.count() << "ms\n";
        // std::cout << ms_double.count() << "ms\n";

    }


}

void VideoToAscii(std::string Video_Name)
{
    cv::VideoCapture capture(Video_Name);
    cv::Mat frame;

    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    else
    {
        VideoConverter *conv = new VideoConverter(capture);
        conv->converter();
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
        { ImgToAscii("720.jpg"); });

    menu.add_row(
        " 2. Video to ascii", [&]()
        { VideoToAscii("360.mp4"); });

    menu.add_row(
        " 3. Animated Ball", [&]()
        { AnimatedBall(); });

    menu.add_row(
        "Exit", nullptr);

    menu.run();
    return 0;
}
