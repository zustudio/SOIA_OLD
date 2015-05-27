
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/AtomReflection.h"
using namespace Environment;

#include "Environment/Global/Public/GlobalsImport.h"

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