//
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"
#include "Environment/Reflection/Element/Public/ElementReflectionProvider.h"
using namespace Environment;

// Global element and atom reflection provider
namespace Environment
{
	AtomReflectionProvider GlobalAtomReflectionProvider;
	ElementReflectionProvider GlobalElementReflectionProvider;
	DLLIMPEXP AtomReflectionProvider* GetAtomReflectionProvider()
	{
		return &GlobalAtomReflectionProvider;
	}
	DLLIMPEXP ElementReflectionProvider* GetElementReflectionProvider()
	{
		return &GlobalElementReflectionProvider;
	}
}