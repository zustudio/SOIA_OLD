
#include "Definitions.h"

#include "Testing.h"
#include "LinearFunction.h"
#include <iostream>
using namespace Environment;

#include "Window.h"


constexpr static const char TEST[] = "ABD";




int main()
{
	X a;
	a.Go<1>();

	auto myWin = SO::Window("Hello World!! :)", pxPoint(1000, 300));
	myWin.Open();
	
	std::string Read;
	std::getline(std::cin, Read);

	std::cout << "hello world ;)" << std::endl;
	std::cout << "result of 1 + 3 is " << ZABS::Math::LinearFunction::get_f(3.0, { -1, 2 });
	return 0;
}