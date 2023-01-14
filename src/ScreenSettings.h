#pragma once

#include <string>

class Screen {
public:
	Screen();

	const float symbolRatio = 11.0f / 24.0f;
	std::string getGradi();
	int64_t getGradiSize();
	void setFont(int FontX = 0, int FontY = 16);
	int getFont();
	void setWindow(int ConsWidth = 120, int ConsHeight = 30);

	int getResolutionX();
	int getResolutionY();
	int getMaxConsoleWidth();
	int getMaxConsoleHeight();

	void fullScreen();
	void clearScreen();
	void moveConsole(int x = 0, int y = 0);
	void gotoXY(int x, int y);
	void gotoZero();
	void reset();

private:
	//std::string gradient = " .:!/r(l1Z4H9W8$@";
	std::string gradient = "@$8W9H4Z1l(r/!:. ";
	int fontSize;
	int currentConsoleWidth;
	int currentConsoleHeight;
	int maxConsoleWidth;
	int maxConsoleHeight;
};
