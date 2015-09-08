
#pragma once

namespace Environment
{
	class LIBIMPEXP pxSize
	{
	public:
		pxSize();
		pxSize(int InWidth, int InHeight);

		int Width;
		int Height;
	};
}