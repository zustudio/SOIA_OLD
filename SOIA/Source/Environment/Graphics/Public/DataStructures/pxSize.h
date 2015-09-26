
#pragma once

#include "pxPoint.h"

namespace Environment
{
	class LIBIMPEXP pxSize
	{
	public:
		pxSize();
		pxSize(int InWidth, int InHeight);

		pxPoint ToPoint();

		int Width;
		int Height;
	};
}