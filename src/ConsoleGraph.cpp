#include <iostream>
#include "ImgToAsciiConverter.h"
#include "area.h"
#include "Menu.h"


void ImgToAscii(char* Img_Name)
{
    AsciiConvert *conv = new AsciiConvert(Img_Name, "ascii.txt");
    conv->converter(true);
    getchar();
    
    delete conv;

}

void AnimatedBall()
{
    Area area(120, 30);
    area.fill();
    
    getchar();

}

int main()
{
    Menu menu("Menu: ");

    menu.add_row(
        " 1. Img to ascii", [&]()
        { ImgToAscii("aska.jpg"); });

    menu.add_row(
        " 2. Video to ascii", nullptr);

    menu.add_row(
        " 3. Animated Ball", [&]()
        { AnimatedBall(); });

    menu.add_row(
        "Exit", nullptr);

    menu.run();
    return 0;
}
