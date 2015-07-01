
#include "Definitions.h"

#include "RClass.h"
using namespace Environment;
#include "ReflectionProviders.h"
#include "RElement.h"

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

bool RClass::IsChildOf(RClass* InClass) const
{
	const RClass* myClass;
	const RClass* mySuper = this;
	do
	{
		myClass = mySuper;
		mySuper = GetElementReflectionProvider()->GetClass(myClass->BaseType);
		if (myClass == InClass)
		{
			return true;
		}
	} while (myClass != RElement::StaticClass());
	return false;
}