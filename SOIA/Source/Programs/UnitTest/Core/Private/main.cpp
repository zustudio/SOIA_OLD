
#include "PrivateDefinitions.h"

#include "VectorTest.h"
#include "MatrixTest.h"
#include "LinFuncTest.h"
using namespace UnitTest::Tests::Environment;

#include "WindowCreation.h"
using namespace UnitTest::Tests::Graphics;

#include "MathTest.h"
using namespace UnitTest;

int main()
{
	VectorTest test1 = VectorTest();
	test1.Execute();

	MatrixTest test2 = MatrixTest();
	test2.Execute();

	LinFuncTest test3 = LinFuncTest();
	test3.Execute();

	MathTest test = MathTest();
	test.Execute();

	WindowCreation test4 = WindowCreation();
	test4.Execute();
}
