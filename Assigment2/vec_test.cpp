#include <iostream>
#include <vector>
#include "vec.h"

int main()
{
	std::vector<CVec2f> vec;
	vec.push_back(CVec2f(0.2, 0.4));
	vec.push_back(CVec2f(70.45, 85.7));
	vec.push_back(CVec2f(789.4567, 324.0897));
	vec.push_back(CVec2f(7094854.245454, 12314153.33536));
	vec.push_back(CVec2f(131231314.0, 98980808.0));

	auto count = vec.size();
	int pass = 0;
	std::cout << "#####################################" << std::endl;
	std::cout << "Test Unit" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CVec2f + CVec2f" << std::endl;
	for (auto v1 : vec)
	{
		for (auto v2 : vec)
		{
			std::cout << "@length@: " << v1.length() << "  " << v2.length() << std::endl;
			std::cout << "@origin@: " << v1.x << "  " << v1.y << std::endl;
			v1.normalize();
			std::cout << "@normalize@: " << v1.x << "  " << v1.y << std::endl;
			//float x = v1.x * v2.x;
			//float y = v1.y * v2.y;
			//CVec2f output(x, y);
			//CVec2f pred(v1 * v2);
			//std::cout << "@output@: " << output.x << "  " << output.y;
			//std::cout << "  @pred@: " << pred.x << "  " << pred.y << std::endl;
		}
	}
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CVec2f - CVec2f" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CVec2f * CVec2f" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CVec2f / CVec2f" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CVec2f == CVec2f" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CVec2f != CVec2f" << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "#####################################" << std::endl;
}