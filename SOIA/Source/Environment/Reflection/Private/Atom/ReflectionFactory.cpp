
#include "Definitions.h"

#include "ReflectionFactory.h"
using namespace Environment;

bool ReflectionFactory::IsAdded(TypeID InType, const std::vector<AtomReflection*>& Reflections)
{
	for (auto reflection : Reflections)
	{
		if (reflection->IsType(InType))
		{
			return true;
		}
	}
	return false;
}