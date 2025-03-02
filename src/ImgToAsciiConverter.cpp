#include "ImgToAsciiConverter.h"

#include <utility>

AsciiConvert::AsciiConvert(sf::Image source)
{
	image = std::move(source);
	resolution = sf::Vector2u{source.getSize().x * screen.symbolRatio.y, source.getSize().y * screen.symbolRatio.x};
}

AsciiConvert::~AsciiConvert()
{
	screen.reset();
}

void AsciiConvert::setImage(const cv::Mat& source)
{
	cv::Mat img_cv_tmp;
    cvtColor(source, img_cv_tmp, cv::COLOR_BGR2RGBA);
	auto newImage = sf::Image(sf::Vector2u{
		static_cast<unsigned int>(img_cv_tmp.cols),
		static_cast<unsigned int>(img_cv_tmp.rows)
	}, img_cv_tmp.ptr());

	image = newImage;
	resolution = sf::Vector2u{newImage.getSize().x * screen.symbolRatio.y, newImage.getSize().y * screen.symbolRatio.x};
}

sf::Vector2u AsciiConvert::getResolution()
{
	return resolution;
}

void AsciiConvert::converter(short fontSize)
{
	if(screen.getFont() != fontSize)
	{
		screen.setFont(0, fontSize);
	}

	const int maxWidth = screen.getMaxConsoleWidth();
	const int maxHeight = screen.getMaxConsoleHeight();

	Screen::moveConsole();

	if (resolution.x > maxWidth)
	{
		float coef = static_cast<float>(resolution.x) / static_cast<float>(maxWidth);
		resolution.x /= coef;
		resolution.y /= coef;
	}

	if(resolution.y > maxHeight)
	{
		float coef = static_cast<float>(resolution.y) / static_cast<float>(maxHeight);
		resolution.x /= coef;
		resolution.y /= coef;
	}
	sf::Image newImage = sf::Image(resolution);

	imageResize(newImage);
	resolution = newImage.getSize();

	float maxBright = brightness(255, 255, 255);

	std::string result;
	for (unsigned int y = 0; y < resolution.y; y++)
	{
		for (unsigned int x = 0; x < resolution.x; x++)
		{
			sf::Color cur_color = newImage.getPixel(sf::Vector2u{x, y});
			float bright = brightness(cur_color.r, cur_color.g, cur_color.b);
			int pixelPosition = (int)((bright / maxBright) * (screen.getGradiSize() - 1));
			result += screen.getGradi()[pixelPosition];
		}
		// result += "\n";
	}
	this->result = result;
}

float AsciiConvert::brightness(int R, int G, int B)
{
	float bright = 0.33f * R + 0.5f * G + 0.16f * B;
	return bright;
}

void AsciiConvert::imageResize(sf::Image &newImage)
{
	const sf::Vector2u oldSize{image.getSize()};
	const sf::Vector2u newSize{newImage.getSize()};

	for (unsigned int y{0u}; y < newSize.y; ++y)
	{
		for (unsigned int x{0u}; x < newSize.x; ++x)
		{
			unsigned int origX{static_cast<unsigned int>(static_cast<double>(x) / newSize.x * oldSize.x)};
			unsigned int origY{static_cast<unsigned int>(static_cast<double>(y) / newSize.y * oldSize.y)};

			sf::Color newColor = image.getPixel(sf::Vector2u{origX, origY});
			sf::Vector2u newCoord{x, y};

			newImage.setPixel(newCoord, newColor);
		}
	}
}

std::string AsciiConvert::asciiOut(bool consoleOut, bool txtOut)
{
	if (txtOut)
	{
		txtresult.open("ascii.txt");
		txtresult << result;
		txtresult.close();
	}
	if (consoleOut)
	{
		Screen::setWindow(resolution.x, resolution.y);
		std::cout << result;
	}
	return result;
}