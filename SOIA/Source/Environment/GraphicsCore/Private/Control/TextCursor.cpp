
#include "Definitions.h"

#include "TextCursor.h"
using namespace Environment;

#include "LinearInterpolation.h"
using namespace std::chrono_literals;

TextCursor::TextCursor(MBoundaries* InBoundaries, std::vector<pxPoint> const & InEdges)
	: GeometryObject(InBoundaries, pxMargins(0,0,0,0), Interpolator<fColor>(fColor(1, 0, 0), new LinearInterpolation<fColor>(530ms)), InEdges),
	OnColor(1, 0, 0),
	OffColor(1, 1, 1)
{}

void TextCursor::Update()
{
	this->RequestUpdate();
	GeometryObject::Update();

	if (!Color.IsInterpolating())
	{
		if (Color == OnColor)
			Color = OffColor;
		else
			Color = OnColor;
	}
}
