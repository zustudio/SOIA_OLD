
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/ReflectionFactory.h"
using namespace Environment;

bool ReflectionFactory::IsTypeAvailable(const std::string& InTypeID)
{
	/*std::regex pattern("class std::(\\w+)<(\\w+),class std::allocator<(\\2)> >");
	auto result = std::smatch();
	bool success = std::regex_match(InTypeID, result, pattern);

	if (success)
	{
		for (int i = 0; i < result.size(); i++)
		{
			std::cout << result[i] << std::endl;
		}
	}*/
	return true;
}