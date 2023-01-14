#include "ImgToAsciiConverter.h"

AsciiConvert::AsciiConvert(cv::Mat source)
{
    setImg(source);
}

AsciiConvert::AsciiConvert(sf::Image source)
{
	img = source;
}

AsciiConvert::~AsciiConvert()
{
	screen.reset();
}

void AsciiConvert::setImg(cv::Mat source)
{
	cv::Mat img_cv_tmp;
    cv::cvtColor(source, img_cv_tmp, cv::COLOR_BGR2RGBA);
	img.create(img_cv_tmp.cols, img_cv_tmp.rows, img_cv_tmp.ptr());
	Resolution = img.getSize();
}

sf::Vector2u AsciiConvert::getResolution()
{
	return Resolution;
}

void AsciiConvert::converter(int fontSize)
{	
	if(screen.getFont() != fontSize)
	{
		screen.setFont(0, fontSize);
	}
	float symbol_ratio = screen.symbolRatio;
	int MaxWidth = screen.getMaxConsoleWidth();
	int MaxHeight = screen.getMaxConsoleHeight() / symbol_ratio;
	screen.moveConsole();

	std::string res = "";
	sf::Image newImg = sf::Image();

	// Resolution.x /= (11.0f / 24.0f);
	if (Resolution.x > MaxWidth)
	{
		float coef = static_cast<float>(Resolution.x) / MaxWidth;
		Resolution.x = MaxWidth;
		Resolution.y /= coef;
	}
	if(Resolution.y > MaxHeight)
	{
		float coef = static_cast<float>(Resolution.y) / MaxHeight;
		Resolution.y = MaxHeight;
		Resolution.x /= coef;
	}

	newImg.create(Resolution.x, Resolution.y * symbol_ratio);

	imageResize(newImg);
	Resolution = newImg.getSize();

	float max_bright = brightness(255, 255, 255);

	for (int y = 0; y < Resolution.y; y++)
	{
		for (int x = 0; x < Resolution.x; x++)
		{
			sf::Color cur_color = newImg.getPixel(x, y);
			float bright = brightness(cur_color.r, cur_color.g, cur_color.b);
			int pixel_pos = (int)((bright / max_bright) * (screen.getGradiSize() - 1));
			res += screen.getGradi()[pixel_pos];
		}
		// res += "\n";
	}
	result = res;
}

float AsciiConvert::brightness(int R, int G, int B)
{
	float bright = 0.33 * R + 0.5 * G + 0.16 * B;
	return bright;
}

void AsciiConvert::imageResize(sf::Image &newImg)
{
	const sf::Vector2u oldSize{img.getSize()};
	const sf::Vector2u newSize{newImg.getSize()};
	for (unsigned int y{0u}; y < newSize.y; ++y)
	{
		for (unsigned int x{0u}; x < newSize.x; ++x)
		{
			unsigned int origX{static_cast<unsigned int>(static_cast<double>(x) / newSize.x * oldSize.x)};
			unsigned int origY{static_cast<unsigned int>(static_cast<double>(y) / newSize.y * oldSize.y)};
			newImg.setPixel(x, y, img.getPixel(origX, origY));
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
		screen.setWindow(Resolution.x, Resolution.y);
		std::cout << result;
	}
	return result;
}