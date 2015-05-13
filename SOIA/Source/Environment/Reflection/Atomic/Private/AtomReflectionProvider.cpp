
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"
using namespace Environment;

#include "Environment/Reflection/Atomic/Classes/SimpleAtomReflection.h"
#include "Environment/Reflection/Atomic/Classes/RPointerReflection.h"
#include "Environment/Reflection/Atomic/Public/ReflectionFactory.h"
#include <sstream>
#include <iomanip>
#include <regex>

AtomReflectionProvider::AtomReflectionProvider()
{
	Reflections.push_back(new SimpleAtomReflection<std::string>(
		[](const std::string& object){return std::string(object); },
		[](const std::string& object){return std::string(object); }));

	Reflections.push_back(new SimpleAtomReflection<int>(
		[](const int& object){return std::to_string(object); },
		[](const std::string& string){return std::atoi(string.c_str()); }));

	Reflections.push_back(new SimpleAtomReflection<double>(
		[](const double& number){ std::ostringstream str; str << std::setprecision(20) << number; return std::string(str.str()); },
		[](const std::string& string) { return std::atof(string.c_str()); }));

	Reflections.push_back(new SimpleAtomReflection<Element_ID>(
		[](const Element_ID& id) {return std::to_string(id.UniqueIdentifier) + "," + id.Name; },
		[](const std::string& string)
	{
		Element_ID id;
		std::regex pattern("([0-9]+),(\\w+)");
		auto result = std::smatch();
		if (std::regex_match(string, result, pattern))
		{
			id.UniqueIdentifier = std::atoi(std::string(result[1]).c_str());
			id.Name = result[2];
		}
		return id; }));

	Reflections.push_back(new RPointerReflection());
}

AtomReflection* AtomReflectionProvider::GetReflection(const std::string& InTypeName)
{
	for (auto reflection : Reflections)
	{
		if (reflection->IsType(InTypeName))
		{
			return reflection;
		}
	}
	return nullptr;
}
