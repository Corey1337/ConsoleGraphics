#include <string>
#include <vector>
#include "ImgToAsciiConverter.h"

class VideoConverter{
public:
    VideoConverter(cv::VideoCapture video);

    ~VideoConverter();

    void converter(int fontSize);

    void ascii_out(bool consoleOut = true, bool txtOut = false);

private:
    cv::Mat frame;
    Screen screen;
    AsciiConvert asciiConverter;
    std::vector<std::string> asciiFrames;
	sf::Vector2u Resolution;
    cv::VideoCapture capture;
    double fps;
    double framesCount;
    double durationMS;
};