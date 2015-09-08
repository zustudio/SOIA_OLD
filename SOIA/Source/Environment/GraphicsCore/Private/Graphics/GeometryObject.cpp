
#include "Definitions.h"

#include "GeometryObject.h"
using namespace Environment;

GeometryObject::GeometryObject(MBoundaries * InBoundaries, pxMargins InMargins, fColor InColor, std::vector<pxPoint> const & InEdges)
	: GraphicsObject(InBoundaries, InMargins),
	Color(InColor),
	Edges(InEdges)
{}

std::vector<pxPoint> GeometryObject::MakeRectangle(pxPoint a, pxPoint b)
{
	std::vector<pxPoint> result;

	result.push_back(a);
	result.push_back(pxPoint(a.X, b.Y));
	result.push_back(b);
	result.push_back(pxPoint(b.X, a.Y));

	return result;
}
