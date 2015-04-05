
#include "MatrixTest.h"

#include <iostream>

using namespace UnitTest::Tests::Environment;
using namespace ZABS::Math;

void MatrixTest::Execute()
{
	Matrix2D<float> A = Matrix2D<float>(2,2,7);
	A.set(0,0,9);
	std::cout << "Matrix Column 0 (sum): " << A.GetColumn(0).Sum();
}
