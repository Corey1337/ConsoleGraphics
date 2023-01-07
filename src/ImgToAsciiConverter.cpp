#include "ImgToAsciiConverter.h"

AsciiConvert::~AsciiConvert()
{
	screen.reset();
}

void AsciiConvert::set_img(cv::Mat source)
{
	img.create(source.cols, source.rows, source.ptr());
}

void AsciiConvert::converter()
{
	Resolution = img.getSize();
	std::string res = "";
	sf::Image newImg = sf::Image();

	// Resolution.x /= (11.0f / 24.0f);
	if (Resolution.x > 1900)
	{
		float coef = static_cast<float>(Resolution.x) / 1899;
		Resolution.x = 1899;
		Resolution.y /= coef;
	}
	newImg.create(Resolution.x, Resolution.y * (11.0f / 24.0f));

	image_resize(newImg);
	Resolution = newImg.getSize();

	float max_bright = brightness(255, 255, 255);

	for (int y = 0; y < Resolution.y; y++)
	{
		for (int x = 0; x < Resolution.x; x++)
		{
			sf::Color cur_color = newImg.getPixel(x, y);
			float bright = brightness(cur_color.r, cur_color.g, cur_color.b);
			int pixel_pos = (int)((bright / max_bright) * (screen.GetGradiSize() - 1));
			res += screen.GetGradi()[pixel_pos];
		}
		res += "\n";
	}
	result = res;
}

float AsciiConvert::brightness(int R, int G, int B)
{
	float bright = 0.33 * R + 0.5 * G + 0.16 * B;
	return bright;
}

void AsciiConvert::image_resize(sf::Image &newImg)
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

std::string AsciiConvert::ascii_out(bool console_out, bool txt_out)
{
	if (txt_out)
	{
		txtresult.open("ascii.txt");
		txtresult << result;
		txtresult.close();
	}
	if (console_out)
	{
		screen.SetFont(0, 1899 / Resolution.x);
		std::cout << result;
		screen.fullScreen();
	}
	return result;
}