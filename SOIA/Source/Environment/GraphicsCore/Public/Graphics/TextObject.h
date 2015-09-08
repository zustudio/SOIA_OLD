
#pragma once

#include "GraphicsObject.h"

#include "MBoundaries.h"
#include "pxMargins.h"
#include "Vector2D.h"
#include "GlyphObject.h"
#include "Font.h"

#include <string>
#include <vector>

namespace Environment
{
	class LIBIMPEXP TextObject : public GraphicsObject
	{
	public:
		TextObject(MBoundaries* InBoundaries, pxMargins InMargins, const std::string& InText);

		//----- content -----
		std::string Text;

	};
}