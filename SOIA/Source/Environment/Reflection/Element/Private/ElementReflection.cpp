
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Element/Public/ElementReflection.h"
using namespace Environment;

ElementReflection::ElementReflection(const std::vector<VoidPointer>& InAttributes)
{
	Attributes = InAttributes;
}