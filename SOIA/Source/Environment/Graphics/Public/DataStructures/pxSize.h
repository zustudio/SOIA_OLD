
#pragma once

#include "pxPoint.h"

namespace Environment
{
	class LIBIMPEXP pxSize
	{
	public:
		pxSize();
		pxSize(int InWidth, int InHeight);

		bool operator==(pxSize const & InOther) const;
		bool operator!=(pxSize const & InOther) const;

		pxPoint ToPoint();

		int Width;
		int Height;
	};
}