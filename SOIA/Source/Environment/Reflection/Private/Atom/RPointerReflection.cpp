
#include "Definitions.h"

#include "RPointerReflection.h"
using namespace Environment;

#include "RPointer.h"

#include <iostream>
#include <string>
#include <regex>

bool RPointerReflection::IsType(const std::string& InTypeID)
{
	return (InTypeID == std::string(TypeID::FromType<RPointer>()));
}

VoidPointer* RPointerReflection::StringToObject(const std::string& InContent)
{
	return nullptr;
}

std::string RPointerReflection::ObjectToString(VoidPointer& InObject)
{
	return "";
}