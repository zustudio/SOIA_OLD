
#include "Definitions.h"

#include "RClassProvider.h"
using namespace Environment;

#include "RElement.h"
#include <iostream>

RClassProvider::RClassProvider()
{}

RClassProvider::~RClassProvider()
{
	for (RClass* rclass : Classes)
	{
		delete rclass;
	}
}

void Environment::RClassProvider::RegisterInternal(RClass * InClass)
{
	if (!GetClass(InClass->GetType()))
	{
		Classes.push_back(InClass);
	}
}

RClass* RClassProvider::GetClass(const TypeID& InType)
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

std::vector<TypeID> RClassProvider::GetTypeList()
{
	std::vector<TypeID> result;
	for (auto rclass : Classes)
	{
		result.push_back(rclass->GetType());
	}
	return result;
}
