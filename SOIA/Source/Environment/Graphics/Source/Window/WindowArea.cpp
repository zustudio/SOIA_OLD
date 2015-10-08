
#include "Definitions.h"
#include "OpenGL.h"

#include "WindowArea.h"
using namespace Env;

WindowArea::WindowArea(MBoundaries * InBoundaries, pxMargins InMargins, StyleSheet InStyle)
	:
	RenderTarget(
		InBoundaries,
		InMargins,
		InStyle),
	Background(
		this,
		pxMargins(0,0,0,0),
		fColor(0.9, 0.9, 0.9),
		[this]() { return GeometryObject::MakeRectangle(pxPoint(0, 0), GetSize().ToPoint()); },
		nullptr,
		EScrollMode::Background)
{
	AddObject(&Background, Layer_Background);
}

void WindowArea::Draw()
{
	glDisable(GL_STENCIL_TEST);
	GetLayer(Layer_Background)->BeginDraw();
}
