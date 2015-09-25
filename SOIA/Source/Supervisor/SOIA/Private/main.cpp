
#include "Definitions.h"

#include "StdDialogue.h"
#include "RWrapper.h"
using namespace Environment;

#include "PersistentRuntime.h"
using namespace Supervisor;


int main()
{
	PersistentRuntime::Initialize(RWrapper<StdDialogue>::StaticClass());
	PersistentRuntime::Run();
}

#if def_BUILD_OS==Windows
#include <Windows.h>
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif
