
#pragma once

#include "GraphicsObject.h"

#include "fColor.h"

namespace Environment
{
	class GeometryObject : public GraphicsObject
	{
	public:
		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, fColor InColor, std::vector<pxPoint> const & InEdges);

		static std::vector<pxPoint> MakeRectangle(pxPoint a, pxPoint b);

		fColor Color;
		std::vector<pxPoint> Edges;
	};
}