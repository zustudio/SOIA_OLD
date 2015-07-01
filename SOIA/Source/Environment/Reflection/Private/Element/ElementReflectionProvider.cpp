
#include "Definitions.h"

#include "ElementReflectionProvider.h"
using namespace Environment;

#include "RElement.h"
#include <iostream>

ElementReflectionProvider::ElementReflectionProvider()
{}

ElementReflectionProvider::~ElementReflectionProvider()
{
	for (RClass* rclass : Classes)
	{
		delete rclass;
	}
}

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