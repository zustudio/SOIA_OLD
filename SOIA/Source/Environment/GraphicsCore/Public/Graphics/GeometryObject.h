
#pragma once

#include "GraphicsObject.h"

#include "fColor.h"

#include <functional>

namespace Environment
{
	class GeometryObject : public GraphicsObject
	{
	public:
		using EdgesFunctionType = std::function<std::vector<pxPoint>()>;

		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, fColor InColor, std::vector<pxPoint> const & InEdges);
		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, fColor InColor, EdgesFunctionType InEdgesFunction);

		virtual void MarkDirty() override;

		static std::vector<pxPoint> MakeRectangle(pxPoint a, pxPoint b);

		fColor Color;
		std::vector<pxPoint> Edges;
		EdgesFunctionType EdgesFunction;
	};
}