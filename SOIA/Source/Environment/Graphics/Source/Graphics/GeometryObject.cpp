
#include "Definitions.h"

#include "GeometryObject.h"
using namespace Environment;

GeometryObject::GeometryObject(MBoundaries * InBoundaries, pxMargins InMargins, Interpolator<fColor> InColor, Interpolator<VectorND<pxPoint>> const & InEdges, EScrollMode InScrollMode)
	: GraphicsObject(InBoundaries, InMargins, InScrollMode),
	Color(InColor),
	Edges(InEdges),
	EdgesFunction(nullptr)
{}

GeometryObject::GeometryObject(MBoundaries * InBoundaries, pxMargins InMargins, Interpolator<fColor> InColor, EdgesFunctionType InEdgesFunction, InterpolationFunction<VectorND<pxPoint>>* InEdgesInterpolatorFunction, EScrollMode InScrollMode)
	: GraphicsObject(InBoundaries, InMargins, InScrollMode),
	Color(InColor),
	Edges(InEdgesFunction(), InEdgesInterpolatorFunction),
	EdgesFunction(InEdgesFunction)
{}

void GeometryObject::Update()
{
	GraphicsObject::Update();

	Color.Update();
	Edges.Update();

	if (bUpdateRequested && EdgesFunction)
	{
		Edges = EdgesFunction();
	}

	if (Edges.IsInterpolating() || Color.IsInterpolating())
	{
		this->RequestUpdate();
	}
}

std::vector<pxPoint> GeometryObject::MakeRectangle(pxPoint a, pxPoint b)
{
	std::vector<pxPoint> result;

	result.push_back(a);
	result.push_back(pxPoint(a.X, b.Y));
	result.push_back(b);
	result.push_back(pxPoint(b.X, a.Y));

	return result;
}
