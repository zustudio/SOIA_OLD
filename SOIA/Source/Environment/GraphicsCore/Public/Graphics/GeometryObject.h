
#pragma once

#include "GraphicsObject.h"

#include "VectorND.h"
#include "fColor.h"
#include "Interpolator.h"

#include <functional>

namespace Environment
{
	class LIBIMPEXP GeometryObject : public GraphicsObject
	{
	public:
		using EdgesFunctionType = std::function<std::vector<pxPoint>()>;

		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, Interpolator<fColor> InColor, Interpolator<VectorND<pxPoint>> const & InEdges);
		GeometryObject(MBoundaries* InBoundaries, pxMargins InMargins, Interpolator<fColor> InColor, EdgesFunctionType InEdgesFunction, InterpolationFunction<VectorND<pxPoint>>* InEdgesInterpolatorFunction = nullptr);

		virtual void Update() override;

		static std::vector<pxPoint> MakeRectangle(pxPoint a, pxPoint b);

		Interpolator<fColor> Color;
		Interpolator<VectorND<pxPoint>> Edges;
		EdgesFunctionType EdgesFunction;
	};
}