
#include "Definitions.h"
#include "RenderThread.h"

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