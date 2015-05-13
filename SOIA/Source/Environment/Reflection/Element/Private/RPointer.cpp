
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Element/Public/RPointer.h"
using namespace Environment;

#include "Environment/Reflection/Element/Public/RElement.h"
#include "Environment/Reflection/Element/Public/RContainer.h"

RPointer::RPointer(RElement* NewTarget, const std::string& InTypeID)
{
	if (NewTarget)
	{
		Target = NewTarget->GetID();
	}
	else
	{
		Target = Element_ID();
		Target.UniqueIdentifier = -1;
	}
	Type = InTypeID;
}
RPointer::RPointer(int InID, const std::string& InTypeID)
{
	Target = Element_ID();
	Target.UniqueIdentifier = InID;
	Type = InTypeID;
}
VoidPointer RPointer::ToVoidPointer()
{
	VoidPointer result = VoidPointer(Resolve());
	result.OverrideType(Type);
	return result;
}
RElement* RPointer::Resolve()
{
	RElement* result = nullptr;
	if (Container)
	{
		result = Container->GetElement<RElement>(Target);
	}
	return result;
}