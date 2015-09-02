
#include "Definitions.h"

#include "AtomConverterHelper.h"
using namespace Environment;

#include "GlobalReflectionProviders.h"
#include "RContainer.h"

std::string AtomConverterHelper::GetAtomString(const VoidPointer& InObject)
{
	return GlobalAtomConverterProvider()->GetConverter(InObject.GetTypeID())->ObjectToString(InObject);
}

VoidPointer* AtomConverterHelper::GetAtomObject(const std::string& InString, const TypeID& InType)
{
	return GlobalAtomConverterProvider()->GetConverter(InType)->StringToObject(InString);
}

RClass* AtomConverterHelper::GetReflectedClass(const TypeID& InID)
{
	return GlobalRClassProvider()->GetClass(InID);
}

RElement* AtomConverterHelper::GetElementByID(const ElementID& InID, RContainer* InContainer)
{
	return InContainer->GetElement<RElement>(InID);
}