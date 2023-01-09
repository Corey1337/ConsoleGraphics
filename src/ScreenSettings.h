#pragma once

#include <string>

class Screen {
public:
	Screen();

	const float symbol_ratio = 11.0f / 24.0f;
	std::string GetGradi();
	int64_t GetGradiSize();
	void SetFont(int FontX = 0, int FontY = 16);
	void SetWindow(int ConsWidth = 120, int ConsHeight = 30);
	int getResolutionX();
	int getResolutionY();
	int getMaxConsoleWidth();
	int getMaxConsoleHeight();
	void fullScreen();
	void clearScreen();
	void moveConsole(int x = 0, int y = 0);
	void gotoxy(int x, int y);
	void gotoZero();
	void reset();

private:
	//std::string gradient = " .:!/r(l1Z4H9W8$@";
	std::string gradient = "@$8W9H4Z1l(r/!:. ";
	int MaxConsoleWidth;
	int MaxConsoleHeight;
};
