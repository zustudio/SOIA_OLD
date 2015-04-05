
#include "LinFuncTest.h"

#include <iostream>

using namespace UnitTest::Tests::Environment;
using namespace ZABS::Math;

void LinFuncTest::Execute()
{
	LinearFunction f = LinearFunction();
	float r = f.get_f(5, {-3, 25});
	std::cout << "f(x) = 25-3x; f(5) = " << r;
}
