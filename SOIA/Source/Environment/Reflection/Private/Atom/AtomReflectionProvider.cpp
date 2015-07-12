
#include "Definitions.h"

#include "AtomReflectionProvider.h"
using namespace Environment;

#include "SimpleAtomReflection.h"
#include "ReflectionFactory.h"
#include "Range.h"
#include <sstream>
#include <iomanip>
#include <regex>

AtomReflectionProvider::AtomReflectionProvider()
{

	Reflect<TypeID>();

	Reflections.push_back(new SimpleAtomReflection<std::string>(
		[](const std::string& object){return std::string(object); },
		[](const std::string& object){return std::string(object); }));

	Reflections.push_back(new SimpleAtomReflection<int>(
		[](const int& object){return std::to_string(object); },
		[](const std::string& string){return std::atoi(string.c_str()); }));

	Reflections.push_back(new SimpleAtomReflection<double>(
		[](const double& number){ std::ostringstream str; str << std::setprecision(20) << number; return std::string(str.str()); },
		[](const std::string& string) { return std::atof(string.c_str()); }));

	Reflections.push_back(new SimpleAtomReflection<Range<int>>(
		[](const Range<int>& InRange) { return std::to_string(InRange.Lower) + "," + std::to_string(InRange.Upper); },
		[](const std::string& InString) { for (auto iter_Middle = InString.begin(); iter_Middle != InString.end(); iter_Middle++)
	{
		if (*iter_Middle == ',') return Range<int>(std::atoi(std::string(InString.begin(), iter_Middle).c_str()), std::atoi(std::string(iter_Middle + 1, InString.end()).c_str()));
	} }));
}

AtomReflectionProvider::~AtomReflectionProvider()
{
	for (AtomReflection* reflection : Reflections)
	{
		delete reflection;
	}
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

std::vector<TypeID> Environment::AtomReflectionProvider::GetTypeList()
{
	std::vector<TypeID> result;
	for (auto reflection : Reflections)
	{
		result.push_back(reflection->GetType());
	}
	return result;
}
