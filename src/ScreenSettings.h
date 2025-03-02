#pragma once

#include <string>
#include "SFML/System/Vector2.hpp"

class Screen {
public:
	Screen();

	const sf::Vector2u symbolRatio {11, 24};
	std::string getGradi();
	short getGradiSize() const;
	void setFont(short fontX = 0, short fontY = 16);
	int getFont() const;
	static void setWindow(short consoleWidth = 120, short consoleHeight = 30);

	static int getResolutionX();
	static int getResolutionY();
	[[nodiscard]] int getMaxConsoleWidth() const;
	[[nodiscard]] int getMaxConsoleHeight() const;

	static void fullScreen();
	static void clearScreen();
	static void moveConsole(int x = 0, int y = 0);
	static void gotoXY(short x, short y);
	static void gotoZero();
	void reset();

private:
	std::string gradient = " .:!/r(l1Z4H9W8$@";
	// std::string gradient = "@$8W9H4Z1l(r/!:. ";
	int fontSize{};
	int currentConsoleWidth{};
	int currentConsoleHeight{};
	int maxConsoleWidth;
	int maxConsoleHeight;
};
