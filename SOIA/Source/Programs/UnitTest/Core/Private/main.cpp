
#include "VectorTest.h"
#include "MatrixTest.h"
#include "LinFuncTest.h"

using namespace UnitTest::Tests::Environment;

int main()
{
	VectorTest test1 = VectorTest();
	test1.Execute();

	MatrixTest test2 = MatrixTest();
	test2.Execute();

	LinFuncTest test3 = LinFuncTest();
	test3.Execute();
}
