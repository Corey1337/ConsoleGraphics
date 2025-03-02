#include "ScreenSettings.h"
#include <cwchar>
#include <iostream>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif

Screen::Screen()
{
#if defined(_WIN32)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	setFont(0, 16);
	fullScreen();
	maxConsoleWidth = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
	maxConsoleHeight = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
	struct winsize w;
	ioctl(fileno(stdout), TIOCGWINSZ, &w);
	maxConsoleWidth = (int)(w.ws_col);
	maxConsoleHeight = (int)(w.ws_row);
#endif // Windows/Linux
	// CONSOLE_SCREEN_BUFFER_INFO csbi;
	// if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	// {
	// 	// an error occourred
	// 	std::cerr << "Cannot determine console size." << std::endl;
	// }
	// else
	// {
		// maxConsoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
		// maxConsoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top;
	// }
	reset();
}

std::string Screen::getGradi()
{
	return gradient;
}

short Screen::getGradiSize() const
{
	return gradient.size();
}

int Screen::getFont() const
{
	// HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// CONSOLE_FONT_INFOEX fontInfo;

	// if (!GetCurrentConsoleFontEx(hOut, TRUE, &fontInfo))
    // 	std::cout << GetLastError() << std::endl;
	// std::cout << std::endl << fontInfo.dwFontSize.Y << "==" << fontSize << std::endl;
	return fontSize;
}

void Screen::setFont(short fontX, short fontY)
{
	if(fontSize != fontY)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = fontX;
		cfi.dwFontSize.Y = fontY;
		fontSize = fontY;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		fullScreen();
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
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

void Screen::setWindow(short consoleWidth, short consoleHeight)
{
	_COORD coord{};
	coord.X = consoleWidth;
	coord.Y = consoleHeight;
	_SMALL_RECT Rect{};
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = consoleHeight - 1;
	Rect.Right = consoleWidth - 1;
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

void Screen::gotoXY(const short x, const short y)
{
	COORD coordinates = {x, y};
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(outputHandle, coordinates);
}

void Screen::moveConsole(const int x, const int y)
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos( consoleWindow, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
}

void Screen::reset()
{
	system("cls");
	gotoZero();
	setFont();
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	setWindow(120, 30);
}

int Screen::getMaxConsoleWidth() const
{
	return maxConsoleWidth;
}
int Screen::getMaxConsoleHeight() const
{
	return maxConsoleHeight;
}