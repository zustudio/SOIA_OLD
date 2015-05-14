
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"
using namespace Environment;

#include "Environment/Reflection/Atomic/Classes/SimpleAtomReflection.h"
#include "Environment/Reflection/Atomic/Public/ReflectionFactory.h"
#include "Environment/Reflection/Element/Public/RPointer.h"
#include <sstream>
#include <iomanip>
#include <regex>

AtomReflectionProvider::AtomReflectionProvider()
{
	// reflect basic types
	Reflect<RPointer>();

	Reflections.push_back(new SimpleAtomReflection<std::string>(
		[](const std::string& object){return std::string(object); },
		[](const std::string& object){return std::string(object); }));

	Reflections.push_back(new SimpleAtomReflection<int>(
		[](const int& object){return std::to_string(object); },
		[](const std::string& string){return std::atoi(string.c_str()); }));

	Reflections.push_back(new SimpleAtomReflection<double>(
		[](const double& number){ std::ostringstream str; str << std::setprecision(20) << number; return std::string(str.str()); },
		[](const std::string& string) { return std::atof(string.c_str()); }));

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
