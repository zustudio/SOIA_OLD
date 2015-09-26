
#pragma once

#include "Definitions.h"
#include "FreeTypeForwardDefinitions.h"

#include "Font.h"

namespace Environment
{
	LIBIMPEXP FT_Library* GetFreeTypeLibrary();
	LIBIMPEXP Font* GetFont(const std::string& InName);
}