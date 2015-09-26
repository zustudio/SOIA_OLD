
#include "Definitions.h"

#include "AtomConverterProvider.h"
using namespace Environment;

#include "Range.h"
#include <sstream>
#include <iomanip>
#include <regex>

AtomConverterProvider::AtomConverterProvider()
{

	Reflect<TypeID>();

	Converters.push_back(new SimpleConverter<std::string>(
		[](const std::string& object){return std::string(object); },
		[](const std::string& object){return std::string(object); }));

	Converters.push_back(new SimpleConverter<int>(
		[](const int& object){return std::to_string(object); },
		[](const std::string& string){return std::atoi(string.c_str()); }));

	Converters.push_back(new SimpleConverter<double>(
		[](const double& number){ std::ostringstream str; str << std::setprecision(20) << number; return std::string(str.str()); },
		[](const std::string& string) { return std::atof(string.c_str()); }));

	Converters.push_back(new SimpleConverter<Range<int>>(
		[](const Range<int>& InRange) { return std::to_string(InRange.Lower) + "," + std::to_string(InRange.Upper); },
		[](const std::string& InString) { for (auto iter_Middle = InString.begin(); iter_Middle != InString.end(); iter_Middle++)
	{
		if (*iter_Middle == ',') return Range<int>(std::atoi(std::string(InString.begin(), iter_Middle).c_str()), std::atoi(std::string(iter_Middle + 1, InString.end()).c_str()));
	} }));
}

AtomConverterProvider::~AtomConverterProvider()
{
	for (AtomConverter* reflection : Converters)
	{
		delete reflection;
	}
}

AtomConverter* AtomConverterProvider::GetConverter(const std::string& InTypeName)
{
	for (auto reflection : Converters)
	{
		if (reflection->IsType(InTypeName))
		{
			return reflection;
		}
	}
	return nullptr;
}

std::vector<TypeID> Environment::AtomConverterProvider::GetTypeList()
{
	std::vector<TypeID> result;
	for (auto reflection : Converters)
	{
		result.push_back(reflection->GetType());
	}
	return result;
}

bool AtomConverterProvider::IsAdded(TypeID InType, const std::vector<AtomConverter*>& Converters)
{
	auto iter_foundConverter = Find(Converters, InType,
		[](AtomConverter * const & InConverter)
		{
			return InConverter->GetType();
		});
	return iter_foundConverter != Converters.end();
}
