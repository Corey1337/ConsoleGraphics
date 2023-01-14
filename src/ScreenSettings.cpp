#include "ScreenSettings.h"
#include <cwchar>
#include <iostream>
#include <Windows.h>

Screen::Screen()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		// an error occourred
		std::cerr << "Cannot determine console size." << std::endl;
	}
	else
	{
		setFont(0, 16);
		fullScreen();	
		maxConsoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
		maxConsoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top;
	}
	reset();
}

std::string Screen::getGradi()
{
	return gradient;
}

int64_t Screen::getGradiSize()
{
	return gradient.size();
}

int Screen::getFont()
{
	// HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// CONSOLE_FONT_INFOEX fontInfo;

	// if (!GetCurrentConsoleFontEx(hOut, TRUE, &fontInfo))
    // 	std::cout << GetLastError() << std::endl;
	// std::cout << std::endl << fontInfo.dwFontSize.Y << "==" << fontSize << std::endl;
	return fontSize;
}

void Screen::setFont(int FontX, int FontY)
{
	if(fontSize != FontY)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = FontX;
		cfi.dwFontSize.Y = FontY;
		fontSize = FontY;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		fullScreen();
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
			// an error occourred
			std::cerr << "Cannot determine console size." << std::endl;
		}
		else
		{
			maxConsoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
			maxConsoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top;
			ShowWindow(GetConsoleWindow(), SW_NORMAL);
		}
	}
}

void Screen::setWindow(int ConsWidth, int ConsHeight)
{
	_COORD coord;
	coord.X = ConsWidth;
	coord.Y = ConsHeight;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = ConsHeight - 1;
	Rect.Right = ConsWidth - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

int Screen::getResolutionX()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int Screen::getResolutionY()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

void Screen::fullScreen()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void Screen::gotoZero()
{
	// gotoxy(1, 1);
	printf("\033[0;0f");
}

void Screen::clearScreen()
{
	// system("cls");
	printf("\033[2J");
}

void Screen::gotoXY(int x, int y)
{
	COORD coordinates = {(short)x, (short)y};
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(outputHandle, coordinates);
}

void Screen::moveConsole(int x, int y)
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos( consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
}

void Screen::reset()
{
	system("cls");
	gotoZero();
	setFont();
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	setWindow(120, 30);
}

int Screen::getMaxConsoleWidth()
{
	return maxConsoleWidth;
}
int Screen::getMaxConsoleHeight()
{
	return maxConsoleHeight;
}