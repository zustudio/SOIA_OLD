
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Classes/RPointerReflection.h"
using namespace Environment;

#include "Environment/Reflection/Element/Public/RPointer.h"

#include <iostream>
#include <string>
#include <regex>

bool RPointerReflection::IsType(const std::string& InTypeID)
{
	return (InTypeID == typeid(RPointer).name());
}

VoidPointer* RPointerReflection::StringToObject(const std::string& InContent)
{
	return nullptr;
}

std::string RPointerReflection::ObjectToString(VoidPointer& InObject)
{
	return "";
}