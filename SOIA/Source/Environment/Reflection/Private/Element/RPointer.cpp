
#include "Definitions.h"

#include "RPointer.h"
using namespace Environment;

#include "RElement.h"
#include "RContainer.h"

RPointer::RPointer(RElement* NewTarget, const TypeID& InType) :
	Type(InType),
	Container(nullptr)
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
}
RPointer::RPointer(int InID, const TypeID& InType) : 
	Target(Element_ID()),
	Type(InType),
	Container(nullptr)
{
	Target.UniqueIdentifier = InID;
}
VoidPointer RPointer::ToVoidPointer()
{
	VoidPointer result = VoidPointer(*new RElement*(Resolve()));
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

RPointer RPointer::FromString(const std::string& InString)
{
	auto result = MatchPattern(InString, "(-?[0-9]+),(\\w+)::(\\w+)\\*");
	if (result.size() == 4)
	{
		std::string ID = result[1];
		std::string Type = result[2] + "::" + result[3] + "*";
		return RPointer(std::atoi(ID.c_str()), TypeID(Type));
	}
	return RPointer(-1, TypeID(""));
}

std::string RPointer::ToString(const RPointer& InObject)
{
	return std::to_string(InObject.Target.UniqueIdentifier) + "," + std::string(InObject.Type);
}