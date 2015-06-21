
#include "Definitions.h"

#include "AtomReflection.h"
using namespace Environment;

#include "ReflectionProviders.h"
#include "RContainer.h"

std::string AtomReflection::GetAtomString(VoidPointer& InObject)
{
	return GetAtomReflectionProvider()->GetReflection(InObject.GetTypeID())->ObjectToString(InObject);
}

VoidPointer* AtomReflection::GetAtomObject(const std::string& InString, const TypeID& InType)
{
	return GetAtomReflectionProvider()->GetReflection(InType)->StringToObject(InString);
}

RClass* AtomReflection::GetReflectedClass(const TypeID& InID)
{
	return GetElementReflectionProvider()->GetClass(InID);
}

std::vector<RElement*> AtomReflection::ObjectToRElements(VoidPointer& InObject)
{
	return {};
}

RElement* AtomReflection::GetElementByID(const Element_ID& InID, RContainer* InContainer)
{
	return InContainer->GetElement<RElement>(InID);
}