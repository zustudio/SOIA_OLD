
#include "PrivateDefinitions.h"

// include my class definition
#include "LinFuncTest.h"
using namespace UnitTest::Tests::Environment;
using namespace ZABS::Math;

#include <iostream>


bool LinFuncTest::Execute()
{
	LinearFunction f = LinearFunction();
	float r = f.get_f(5, {-3, 25});
	std::cout << "f(x) = 25-3x; f(5) = " << r;
	return true;
}
