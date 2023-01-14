#include "ScreenSettings.h"
#include <vector>
#include <string>

class Area {
public:
	Area(int width, int height);

	~Area();

	void fill();
	
private:
	Screen screen;
	std::vector<std::string> area;
	int width;
	int height;
	float aspectRatio;
	float simbolRatio;
};