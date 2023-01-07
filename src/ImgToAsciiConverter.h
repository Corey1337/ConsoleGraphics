
#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "ScreenSettings.h"
#include <opencv2/opencv.hpp>

class AsciiConvert {
public:

	~AsciiConvert();

	void set_img(cv::Mat source);
	
	void converter();

	std::string ascii_out(bool console_out = true, bool txt_out = true);

	float brightness(int R, int G, int B);

	void image_resize(sf::Image& newImg);

private:
	Screen screen;
	sf::Image img;
	std::ofstream txtresult;
	std::string result;
	sf::Vector2u Resolution;
};