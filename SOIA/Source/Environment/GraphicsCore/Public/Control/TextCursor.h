
#pragma once

#include "GeometryObject.h"

namespace Environment
{
	class TextCursor : public GeometryObject
	{
	public:
		TextCursor(MBoundaries* InBoundaries, std::vector<pxPoint> const & InEdges);
		virtual void Update() override;

	private:
		fColor OnColor;
		fColor OffColor;
	};
}