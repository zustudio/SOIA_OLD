
#include "VectorTest.h"
#include "MatrixTest.h"
#include "LinFuncTest.h"
using namespace UnitTest::Tests::Environment;

#include "WindowCreation.h"
using namespace UnitTest::Tests::Graphics;


int main()
{
	VectorTest test1 = VectorTest();
	test1.Execute();

	MatrixTest test2 = MatrixTest();
	test2.Execute();

	LinFuncTest test3 = LinFuncTest();
	test3.Execute();

	WindowCreation test4 = WindowCreation();
	test4.Execute();
}
