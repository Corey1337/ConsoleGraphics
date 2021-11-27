#include <iostream>
#include "ImgToAsciiConverter.h"

int main()
{
    
    AsciiConvert* conv = new AsciiConvert("test1.jpg", "ascii.txt");
    conv->converter(true);
    delete conv;

	return 0;
}
