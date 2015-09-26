
#include "Definitions.h"

#include "CalculatorWindow.h"
#include "GlobalRenderThread.h"
using namespace Environment;
using namespace Programs;

int main()
{
	CalculatorWindow calculator;

	GlobalRenderThread()->Start();
	GlobalRenderThread()->AddWindow(&calculator);
	GlobalRenderThread()->Join();
}

#if def_BUILD_OS==Windows
#include <Windows.h>
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif