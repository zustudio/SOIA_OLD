
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
	std::regex pattern("-?([0-9]+),class (\\w+)::(\\w+) \\*");
	auto result = std::smatch();
	bool success = std::regex_match(InContent, result, pattern);

	if (success)
	{
		std::string ID = result[1];
		std::string Type = "class " + std::string(result[2]) + "::" + std::string(result[3]) + " *";
		return new VoidPointer(*new RPointer(std::atoi(ID.c_str()),Type));
	}
	else
		return nullptr;
}

std::string RPointerReflection::ObjectToString(VoidPointer& InObject)
{
	RPointer* pointer = InObject.CastTo<RPointer>();
	return std::to_string(pointer->Target.UniqueIdentifier) + "," + pointer->Type;
}