#pragma once
#include <string>

class Screen {
public:
	std::string GetGradi();
	int64_t GetGradiSize();
	void SetFont(int FontX = 0, int FontY = 16);
	void SetWindow(int ConsWidth = 120, int ConsHeight = 30);
	int getResolutionX();
	int getResolutionY();
	void fullScreen();

private:
	//std::string gradient = " .:!/r(l1Z4H9W8$@";
	std::string gradient = "@$8W9H4Z1l(r/!:. ";

};
