
#include "Definitions.h"
#include "FreeType.h"

#include "Font.h"
using namespace Environment;

#include "FreeTypeProvider.h"
#include "GlobalLogger.h"

Font::Font(const std::string& InFontName)
	:
	Name(InFontName)
{
}

void Environment::Font::Load()
{
	if (FT_New_Face(*GetFreeTypeLibrary(), Name.c_str(), 0, &FTFace))
	{
		LOG("Could not load font: " + Name, Logger::Severity::Error);
	}
}

bool Environment::Font::operator==(const Font & InOther)
{
	return InOther.Name == Name;
}
