
#include "Definitions.h"

#include "Testing.h"
#include "LinearFunction.h"
#include <iostream>
using namespace Environment;


constexpr static const char TEST[] = "ABD";




int main()
{
	X a;
	a.Go<1>();
	std::cout << "hello world ;)" << std::endl;
	std::cout << "result of 1 + 3 is " << ZABS::Math::LinearFunction::get_f(3.0, { -1, 2 });
	return 0;
}