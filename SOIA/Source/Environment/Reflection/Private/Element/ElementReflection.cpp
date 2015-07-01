
#include "Definitions.h"

#include "ElementReflection.h"
using namespace Environment;

ElementReflection::ElementReflection(const std::vector<VoidPointer>& InAttributes)
	:
	Attributes(InAttributes)
{}

ElementReflection::ElementReflection(const std::vector<VoidPointer*>& InAttributes)
{
	Attributes.clear();

	for (auto attribute : InAttributes)
	{
		Attributes.push_back(VoidPointer(*attribute));
	}
}