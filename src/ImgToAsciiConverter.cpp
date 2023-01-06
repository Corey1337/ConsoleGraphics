#include "ImgToAsciiConverter.h"

AsciiConvert::AsciiConvert(const char* source, const char* result) {
	txtresult.open(result);
	img.loadFromFile(source);
	
}

AsciiConvert::~AsciiConvert() {
	screen.reset();
	txtresult.close();
}

void AsciiConvert::converter(bool consout) {

	std::string res = "";

	sf::Vector2u Resolution = img.getSize();

	sf::Image newImg = sf::Image();
	//Resolution.x /= (11.0f / 24.0f);
	if (Resolution.x > 1900)
	{
		float coef = static_cast<float>(Resolution.x) / 1899;
		Resolution.x = 1899;
		Resolution.y /= coef;
	}
	newImg.create(Resolution.x, Resolution.y * (11.0f / 24.0f));
	
	image_resize(img, newImg);
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
	txtresult << res;
	if (consout)
	{
		screen.SetFont(0, 1899 / Resolution.x);
		std::cout << res;
		screen.fullScreen();
	}

}

float AsciiConvert::brightness(int R, int G, int B) {
	float bright = 0.33 * R + 0.5 * G + 0.16 * B;
	return bright;
}

void AsciiConvert::image_resize(sf::Image& img, sf::Image& newImg)
{	
	const sf::Vector2u oldSize{ img.getSize() };
	const sf::Vector2u newSize{ newImg.getSize() };
	for (unsigned int y{ 0u }; y < newSize.y; ++y)
	{
		for (unsigned int x{ 0u }; x < newSize.x; ++x)
		{
			unsigned int origX{ static_cast<unsigned int>(static_cast<double>(x) / newSize.x * oldSize.x) };
			unsigned int origY{ static_cast<unsigned int>(static_cast<double>(y) / newSize.y * oldSize.y) };
			newImg.setPixel(x, y, img.getPixel(origX, origY));
		}
	}
}