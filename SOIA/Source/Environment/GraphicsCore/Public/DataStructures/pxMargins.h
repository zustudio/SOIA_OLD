
#pragma once

namespace Environment
{
	struct LIBIMPEXP pxMargin
	{
		pxMargin(int InValue)
			:
			Value(InValue)
		{}

		operator int()
		{
			return Value;
		}

		int FromSize(int InSize)
		{
			return -InSize;
		}

	private:
		int Value;
	};

	class LIBIMPEXP pxMargins
	{
	public:
		pxMargins();
		pxMargins(pxMargin InLeft, pxMargin InTop, pxMargin InRight, pxMargin InBottom);

		pxMargin Left;
		pxMargin Top;
		pxMargin Right;
		pxMargin Bottom;
	};
}