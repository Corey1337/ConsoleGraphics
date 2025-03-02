#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "ScreenSettings.h"
#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>

class AsciiConvert {
public:

	AsciiConvert() = default;

	explicit AsciiConvert(sf::Image source);

	~AsciiConvert();

	void setImage(const cv::Mat& source);
	
	void converter(short fontSize);

	std::string asciiOut(bool consoleOut = true, bool txtOut = true);

	static float brightness(int R, int G, int B);

	void imageResize(sf::Image& newImage);

	sf::Vector2u getResolution();

private:
	Screen screen;
	sf::Image image;
	std::ofstream txtresult;
	std::string result;
	sf::Vector2u resolution;
};