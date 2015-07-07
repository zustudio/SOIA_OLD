
#pragma once

#include "Vector2D.h"

#include "DataUnravelerTemplate.h"

namespace Environment
{
	using Vector2DFloatUnraveler = DataUnravelerTemplate<Vector2D<float>, float, &Vector2D<float>::X, &Vector2D<float>::Y>;
}