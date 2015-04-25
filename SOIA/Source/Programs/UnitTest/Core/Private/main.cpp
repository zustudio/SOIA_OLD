
#include "Programs/UnitTest/Core/Classes/PrivateDefinitions.h"
//
//#include "Programs/UnitTest/Tests/Environment/Public/VectorTest.h"
//#include "Programs/UnitTest/Tests/Environment/Public/MatrixTest.h"
//#include "Programs/UnitTest/Tests/Environment/Public/LinFuncTest.h"
//using namespace UnitTest::Tests::Environment;

#include "Programs/UnitTest/Tests/Graphics/Public/WindowCreation.h"
using namespace UnitTest::Tests::Graphics;

#include "Programs/UnitTest/Tests/Supervisor/Public/MathTest.h"
using namespace UnitTest;

int main()
{
	/*VectorTest test1 = VectorTest();
	test1.Execute();

	MatrixTest test2 = MatrixTest();
	test2.Execute();

	LinFuncTest test3 = LinFuncTest();
	test3.Execute();*/

	MathTest test = MathTest();
	test.Execute();

	/*ObjectTest test4 = ObjectTest();
	test4.Execute();*/

	WindowCreation test5 = WindowCreation();
	test5.Execute();
}
