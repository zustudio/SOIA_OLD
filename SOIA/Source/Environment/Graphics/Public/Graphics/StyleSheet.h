
#pragma once

#include "fColor.h"
#include "TextStyle.h"

namespace Environment
{
	class StyleSheet
	{
	public:
		StyleSheet(fColor InBackGround, TextStyle Heading, TextStyle Content);

		fColor Background;
		TextStyle Heading;
		TextStyle Content;
	};
}
