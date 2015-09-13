
#include "Definitions.h"

#include "iTriangle.h"
using namespace Environment;

iTriangle::iTriangle()
	:
	A(0),
	B(0),
	C(0)
{}

iTriangle::iTriangle(int InA, int InB, int InC)
	:
	A(InA),
	B(InB),
	C(InC)
{}