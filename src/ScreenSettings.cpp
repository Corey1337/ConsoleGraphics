
#include "ScreenSettings.h"
#include <cwchar>
#include <Windows.h>

std::string Screen::GetGradi() {
	return gradient;
}

int64_t Screen::GetGradiSize() {
	return gradient.size();
}

void Screen::SetFont(int FontX, int FontY) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = FontX;                   // Width of each character in the font
	cfi.dwFontSize.Y = FontY;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Screen::SetWindow(int ConsWidth, int ConsHeight) {
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

int Screen::getResolutionX() {
	return GetSystemMetrics(SM_CXSCREEN);
}

int Screen::getResolutionY() {
	return GetSystemMetrics(SM_CYSCREEN);
}

void Screen::fullScreen() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //������ ����� ��� �����
}

void Screen::clearScreen() {
	gotoxy(1, 1);
	printf("\033[0;0f");
}

void Screen::s_clearScreen() {
	system("cls");
}

void Screen::gotoxy(int x, int y) {
	COORD coordinates = { (short)x, (short)y };
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(outputHandle, coordinates);
}

void Screen::reset() {
	s_clearScreen();
	SetFont();
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	SetWindow(120, 30);
}