#include "area.h"
#include "ScreenSettings.h"
#include <iostream>
#include <cmath>


Area::Area(int width, int height) {
	Screen screen;

	this->width = width;
	this->height = height;

	screen.SetWindow(width, height);
	screen.SetFont();

	aspect_ratio = (float)width / height;
	simbol_ratio = screen.symbol_ratio;

	std::string str(width, ' ');
	area.resize(height, str);
}

void Area::fill() {
	/*HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;*/
	for (int t = 0; t < 10000; t++)
	{
		Screen screen;
		
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				float x = (float)i / width * 2.0f - 1.0f;
				float y = (float)j / height * 2.0f - 1.0f;

				x *= aspect_ratio * simbol_ratio;
				x += sin(t * 0.01);
				char pix = ' ';
				/*if (x * x + y * y < 1)
					pix = '@';*/
				float length = sqrt(x * x + y * y);
				int color = length / screen.GetGradiSize() * 100;
				if (color < 0)
					color = 0;
				else if (color >= screen.GetGradiSize())
					color = screen.GetGradiSize() - 1;
				pix = screen.GetGradi()[color];
				//pix = screen.GetGradi()[screen.GetGradiSize() - 1 - color]; invert pixels color

				area[j][i] = pix;
			}
		}
		for (int i = 0; i < height; i++)
		{
			printf(area[i].c_str(), '\n');
		}
		//WriteConsoleOutputCharacter(hConsole, area, width * height, { 0, 0 }, &dwBytesWritten);
		screen.clearScreen();
	}

	
}



Area::~Area() {

}

