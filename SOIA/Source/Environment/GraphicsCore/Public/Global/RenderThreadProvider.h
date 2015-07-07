
#pragma once

#include "Definitions.h"
#include "OpenGL.h"

#include "RenderThread.h"


namespace Environment
{
	LIBIMPEXP RenderThread*  GetRenderThread();
}
GLEWContext* glewGetContext();

