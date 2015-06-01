
#include "Definitions.h"

#include "ElementReflectionProvider.h"
using namespace Environment;

#include "RElement.h"

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