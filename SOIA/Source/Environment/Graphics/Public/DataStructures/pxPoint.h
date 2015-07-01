#pragma once

#include "Vector2D.h"

using namespace ZABS::Math;

namespace Graphics
{
	class __declspec(dllexport) pxPoint : public Vector2D<int>
	{
	public:
		//---- init ----
		pxPoint(int newX = 0, int newY = 0);
		pxPoint(const Vector2D<int> &equalVector2D);
		//---- interoperation with fPoint ----
		pxPoint(const Vector2D<float> &equalVector2D) {X = int(equalVector2D.X); Y = int(equalVector2D.Y); }
		operator Vector2D<float>() {return Vector2D<float>(float(X), float(Y));}
	};
}
