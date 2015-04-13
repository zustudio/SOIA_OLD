
#include "PrivateDefinitions.h"

#include "Programs/UnitTest/Tests/Supervisor/Public/MathTest.h"
using namespace UnitTest;

#include "Supervisor/Logica/Public/SchroedingerApplication.h"
using namespace Supervisor;

bool MathTest::Execute()
{
	auto app = SchroedingerApplication();

	app.Execute();
	return true;
}