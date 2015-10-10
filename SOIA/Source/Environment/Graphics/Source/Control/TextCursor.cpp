
#include "Definitions.h"

#include "TextCursor.h"
using namespace Environment;

#include "LinearInterpolation.h"
#include "InstantInterpolation.h"
#include "LimitedExponentialInterpolation.h"
#include "SmoothInterpolation.h"
using namespace std::chrono_literals;
#include "GlobalLogger.h"

TextCursor::TextCursor(MBoundaries* InBoundaries, std::function<std::vector<pxPoint>()> InCallback)
	: GeometryObject(InBoundaries, pxMargins(0, 0, 0, 0), Interpolator<fColor>(fColor(1, 0, 0), new LinearInterpolation<fColor>(150ms)), InCallback, new LimitedExponentialInterpolation<VectorND<pxPoint>>(120ms)),
	Position(0),
	OnColor(0, 0, 0),
	OffColor(1, 1, 1, 0)
{}

void TextCursor::Update()
{
	GeometryObject::Update();

	auto now = std::chrono::system_clock::now();
	if (bVisible && now - PreviousToggle > 520ms)
	{
		PreviousToggle = now;
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
		Color = OnColor;
	else
		Color = fColor(0, 0, 0, 0);
}

int TextCursor::GetPosition()
{
	return Position;
}

void TextCursor::SetPosition(int InPosition)
{
	Position = InPosition;
	Color = OnColor;
	RequestUpdate();
}
