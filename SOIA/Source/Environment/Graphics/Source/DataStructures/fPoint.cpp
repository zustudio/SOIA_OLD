
#include "Definitions.h"

#include "Vector2D.h"
#include "fPoint.h"

using namespace Environment;

//////////////////////////////////////////////////////////////////////////////////
// init
fPoint::fPoint(float newX, float newY) : Vector2D<float>(newX, newY)
{

}
fPoint::fPoint(const Vector2D<float> &equalPoint)
{
	X = equalPoint.X;
	Y = equalPoint.Y;
}
fPoint::~fPoint() {}

