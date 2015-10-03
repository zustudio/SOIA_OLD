

#include <iostream>

#include "GlobalRenderThread.h"
using namespace Environment;

#include "VertexBufferTemplate.h"
#include "DataUnravelerTemplate.h"
#include "GraphicsLayer.h"
#include "TextLayer.h"
#include "FreeTypeProvider.h"

#include "FileSystemProvider.h"

#include "TestWindow.h"
#include "GlobalLogger.h"

int main()
{
	//GlobalLogger()->SetMinimalSeverity(Logger::Severity::DebugInfo);
	GlobalRenderThread()->Start();
	GlobalRenderThread()->AddWindow(new TestWindow());
	GlobalRenderThread()->Join();
	return 0;
}

#if def_BUILD_OS==Windows
#include <Windows.h>
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif
