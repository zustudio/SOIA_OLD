
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Classes/VectorAtomReflection.h"
using namespace Environment;



bool VectorAtomReflection::IsType(const std::string& InType)
{
		std::regex pattern("class std::(\\w+)<(.+),class std::allocator<(\\2)> >");
		auto result = std::smatch();
		bool success = std::regex_match(InType, result, pattern);

		if (success)
		{
			/*for (int i = 0; i < result.size(); i++)
			{
				std::cout << result[i] << std::endl;
			}*/
		}
		return success;
}

