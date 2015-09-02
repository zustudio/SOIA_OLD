
#include "Definitions.h"
#include "FreeType.h"
#include "Font.h"
#include "GlobalLogger.h"
#include "CPPExtensions.h"

namespace Environment
{
	FT_Library* GlobalFreeTypeLibrary = new FT_Library();
	LIBIMPEXP FT_Library* GetFreeTypeLibrary()
	{
		if (*GlobalFreeTypeLibrary)
			return GlobalFreeTypeLibrary;
		else
		{
			if (FT_Init_FreeType(GlobalFreeTypeLibrary))
				LOG("Could not init FreeType library", Logger::Severity::Error);
			return GlobalFreeTypeLibrary;
		}
	}

	std::vector<Font> GlobalFonts;
	LIBIMPEXP Font* GetFont(const std::string& InName)
	{
		auto iter_Font = std::find(GlobalFonts.begin(), GlobalFonts.end(), Font(InName));

		if (iter_Font == GlobalFonts.end())
		{
			Font font = Font(InName);
			font.Load();
			GlobalFonts.push_back(std::move(font));
			auto back = &*(GlobalFonts.end() - 1);
			return back;
		}
		else
		{
			return const_cast<Font*>(&*iter_Font);
		}
	}
}