
#include "Programs/UnitTest/Core/Classes/PrivateDefinitions.h"

//This class
#include "Programs/UnitTest/Tests/Environment/Public/VectorTest.h"

//used in code
#include <iostream>

using namespace UnitTest::Tests::Environment;
using namespace ZABS::Math;

void VectorTest::Execute()
{
	Vector2D<float> a = Vector2D<float>(4,8);
	std::cout << "Hallo!" << a.Length();
}
