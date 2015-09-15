
#pragma once

#include "GraphicsObject.h"

#include "fColor.h"
#include "Interpolator.h"

#include <functional>

namespace Environment
{
	class GeometryObject : public GraphicsObject
	{
	public:
		using EdgesFunctionType = std::function<std::vector<pxPoint>()>;

		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, Interpolator<fColor> InColor, std::vector<pxPoint> const & InEdges);
		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, Interpolator<fColor> InColor, EdgesFunctionType InEdgesFunction);

		virtual void Update() override;

		static std::vector<pxPoint> MakeRectangle(pxPoint a, pxPoint b);

		Interpolator<fColor> Color;
		std::vector<pxPoint> Edges;
		EdgesFunctionType EdgesFunction;
	};
}