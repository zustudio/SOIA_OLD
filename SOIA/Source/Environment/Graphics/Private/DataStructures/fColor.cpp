
#include "Definitions.h"

#include "fColor.h"

using namespace Graphics;

fColor::fColor()
{
	R = 1;
	G = 1;
	B = 1;
	A = 1;
}
fColor::fColor(float NewR, float NewG, float NewB, float NewA)
{
	R = NewR;
	G = NewG;
	B = NewB;
	A = NewA;
}
fColor::~fColor() {}

void fColor::Set(float NewR, float NewG, float NewB, float NewA)
{
	R = NewR;
	G = NewG;
	B = NewB;
	A = NewA;
}
