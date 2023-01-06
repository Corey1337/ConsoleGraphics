
#include <vector>
#include <string>

class Area {
public:
	Area(int width, int height);

	void fill();


	~Area();
private:
	std::vector<std::string> area;
	int width;
	int height;
	float aspect_ratio;
	float simbol_ratio;
};