
#include "Definitions.h"
#include "RenderThread.h"
#include "GlobalLogger.h"
#include <string>

namespace Environment
{
	RenderThread* CurrentRenderThread = nullptr;
	LIBIMPEXP RenderThread* GlobalRenderThread()
	{
		if (CurrentRenderThread)
			return CurrentRenderThread;
		else
			return CurrentRenderThread = new RenderThread();
	}
}
LIBIMPEXP GLEWContext* glewGetContext()
{
	return Environment::GlobalRenderThread()->CurrentWindow->GlewContext;
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