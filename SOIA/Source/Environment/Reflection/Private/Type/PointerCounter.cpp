
#include "Definitions.h"

#include "PointerCounter.h"
using namespace Environment;

PointerCounter::PointerCounter()
	:
	ClonedPointerCount(0)
{}

void PointerCounter::Increase()
{
	ClonedPointerCount++;
}
bool PointerCounter::Decrease()
{
	ClonedPointerCount--;
	return ClonedPointerCount > 0;
}
