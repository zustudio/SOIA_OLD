
#pragma once

#include "Texture2D.h"

#include "Font.h"

namespace Environment
{
	class FontTexture2D : public Texture2D
	{
		FontTexture2D(Font const & InFont);
	};
}