#pragma once

#include <string>
#include <vector>
#include "ImgToAsciiConverter.h"

class VideoConverter{
public:
    explicit VideoConverter(const cv::VideoCapture& video);

    ~VideoConverter();

    void converter(short fontSize);

    void asciiOut(bool consoleOut = true, bool txtOut = false);

private:
    cv::Mat frame;
    Screen screen;
    AsciiConvert asciiConverter;
    std::vector<std::string> asciiFrames;
	sf::Vector2u resolution;
    cv::VideoCapture capture;
    double fps;
    double framesCount;
    double durationMS;
};