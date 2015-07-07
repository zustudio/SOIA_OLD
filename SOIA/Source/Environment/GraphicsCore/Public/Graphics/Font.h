
#pragma once

#include "FreeTypeForwardDefinitions.h"

#include <string>

namespace Environment
{
	class Font
	{
	public:
		Font(const std::string& InFontName);

		void Load();

		bool operator==(const Font& InOther);
		std::string Name;
		FT_Face FTFace;
	};
}