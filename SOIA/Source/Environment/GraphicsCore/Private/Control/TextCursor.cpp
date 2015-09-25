
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
	OnColor(0, 0, 0),
	OffColor(1, 1, 1, 0)
{}

void TextCursor::Update()
{
	GeometryObject::Update();

	if (bVisible && !Color.IsInterpolating())
	{

		if (Color == OnColor)
			Color = OffColor;
		else
			Color = OnColor;
	}

}

void TextCursor::SetVisibility(bool Visible)
{
	bVisible = Visible;
	if (bVisible)
		Color = fColor(0, 0, 0, 0);
	else
		Color = OnColor;
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
