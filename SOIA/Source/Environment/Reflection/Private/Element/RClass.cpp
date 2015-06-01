
#include "Definitions.h"

#include "RClass.h"
using namespace Environment;

RClass::RClass(const TypeID &InType, const TypeID& InBaseType) :
	Type(InType.RemoveSuffix_Base()),
	BaseType(InBaseType.RemoveSuffix_Base())
{}

RClass::~RClass()
{

}

TypeID RClass::GetType()
{
	return Type;
}

bool RClass::IsType(const TypeID& InType)
{
	return (InType == Type);
}
