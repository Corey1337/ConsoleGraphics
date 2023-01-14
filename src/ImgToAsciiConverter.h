#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "ScreenSettings.h"
#include <opencv2/opencv.hpp>
#include <chrono>

class AsciiConvert {
public:

	AsciiConvert() = default;
	
	AsciiConvert(cv::Mat source);

	AsciiConvert(sf::Image source);

	~AsciiConvert();

	void setImg(cv::Mat source);
	
	void converter(int fontSize);

	std::string asciiOut(bool consoleOut = true, bool txtOut = true);

	float brightness(int R, int G, int B);

	void imageResize(sf::Image& newImg);

	sf::Vector2u getResolution();

private:
	Screen screen;
	sf::Image img;
	std::ofstream txtresult;
	std::string result;
	sf::Vector2u Resolution;
};