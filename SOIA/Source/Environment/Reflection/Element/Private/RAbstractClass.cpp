
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Element/Public/RAbstractClass.h"
using namespace Environment;

RAbstractClass::RAbstractClass(const std::string& InTypeID, const std::string& InSuperTypeID) : RClass(InTypeID, InSuperTypeID)
{}

bool RAbstractClass::IsAbstract()
{
	return true;
}

RElement* RAbstractClass::GetDefaultObject()
{
	return nullptr;
}