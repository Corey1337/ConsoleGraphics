#include <iostream>
#include "ImgToAsciiConverter.h"

int main()
{
    
    AsciiConvert* conv = new AsciiConvert("test5.gif", "ascii.txt");
    conv->converter(true);
    delete conv;

	return 0;
}
