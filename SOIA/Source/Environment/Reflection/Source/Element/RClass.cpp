
#include "Definitions.h"

#include "RClass.h"
using namespace Environment;
#include "GlobalReflectionProviders.h"
#include "RElement.h"

RClass::RClass(const TypeID &InType, const TypeID& InBaseType) :
	Type(InType),
	BaseType(InBaseType)
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
		mySuper = GlobalRClassProvider()->GetClass(myClass->BaseType);
		if (myClass == InClass)
		{
			return true;
		}
	} while (myClass != RElement::StaticClass());
	return false;
}