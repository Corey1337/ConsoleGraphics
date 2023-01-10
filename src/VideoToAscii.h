#include <string>
#include <vector>

#include "ImgToAsciiConverter.h"

class VideoConverter{
public:
    VideoConverter(cv::VideoCapture video);
    ~VideoConverter();
    void converter();
    void ascii_out();
private:
    cv::Mat frame;
    Screen screen;
    AsciiConvert ascii_converter;
    std::vector<std::string> ascii_frames;
	sf::Vector2u Resolution;
    cv::VideoCapture capture;
    double fps;
    double frames_Count;
    double duration_ms;
};