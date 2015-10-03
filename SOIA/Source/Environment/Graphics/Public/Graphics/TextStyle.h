
#pragma once

#include "Font.h"
#include "fColor.h"

namespace Environment
{
	class TextStyle
	{
	public:
		TextStyle(Font* , int InSize, fColor InColor);

		Font* TextFont;
		int Size;
		fColor Color;
	};
}