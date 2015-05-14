
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Element/Public/ElementReflectionProvider.h"
using namespace Environment;

#include "Environment/Reflection/Element/Public/RElement.h"

void ElementReflectionProvider::Register(RClass* InClass)
{
	Classes.push_back(InClass);
}

RClass* ElementReflectionProvider::GetClass(const TypeID& InType)
{
	TypeID RealType = InType.RemoveSuffix_Base();
	for (RClass* testClass : Classes)
	{
		if (testClass->IsType(RealType))
		{
			return testClass;
		}
	}
	return nullptr;
}