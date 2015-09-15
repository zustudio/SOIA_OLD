
#include "Definitions.h"

#include "TextCursor.h"
using namespace Environment;

#include "LinearInterpolation.h"
#include "InstantInterpolation.h"
#include "LimitedExponentialInterpolation.h"
using namespace std::chrono_literals;
#include "GlobalLogger.h"

TextCursor::TextCursor(MBoundaries* InBoundaries, std::function<std::vector<pxPoint>()> const & InEdges)
	: GeometryObject(InBoundaries, pxMargins(0,0,0,0), Interpolator<fColor>(fColor(1, 0, 0), new InstantInterpolation<fColor>(520ms)), InEdges, new LimitedExponentialInterpolation<VectorND<pxPoint>>(80ms)),
	Position(0),
	OnColor(1, 0, 0),
	OffColor(1, 1, 1)
{}

void TextCursor::Update()
{
	GeometryObject::Update();

	if (Edges.IsInterpolating() || Color.IsInterpolating())
	{
		this->RequestUpdate();
	}

	if (!Color.IsInterpolating())
	{

		if (Color == OnColor)
			Color = OffColor;
		else
			Color = OnColor;
	}

}

int TextCursor::GetPosition()
{
	return Position;
}

void TextCursor::SetPosition(int InPosition)
{
	Position = InPosition;
	Color = OnColor;
}
