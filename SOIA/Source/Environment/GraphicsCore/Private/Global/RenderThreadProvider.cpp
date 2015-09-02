
#include "Definitions.h"
#include "RenderThread.h"
#include "GlobalLogger.h"
#include <string>

namespace Environment
{
	RenderThread* GlobalRenderThread = nullptr;
	LIBIMPEXP RenderThread* GetRenderThread()
	{
		if (GlobalRenderThread)
			return GlobalRenderThread;
		else
			return GlobalRenderThread = new RenderThread();
	}
}
LIBIMPEXP GLEWContext* glewGetContext()
{
	return Environment::GetRenderThread()->CurrentWindow->GlewContext;
}

void CheckGLError()
{
	// check OpenGL error
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		Environment::GlobalLogger()->Log("OpenGL error: " + std::to_string(err), Environment::Logger::Severity::Error);
	}
}