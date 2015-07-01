//
#include "Definitions.h"

#include "AtomReflectionProvider.h"
#include "ElementReflectionProvider.h"
using namespace Environment;

// Global element and atom reflection provider
namespace Environment
{

	AtomReflectionProvider GlobalAtomReflectionProvider;
	ElementReflectionProvider GlobalElementReflectionProvider;
	LIBIMPEXP AtomReflectionProvider* GetAtomReflectionProvider()
	{
		return &GlobalAtomReflectionProvider;
	}
	LIBIMPEXP ElementReflectionProvider* GetElementReflectionProvider()
	{
		return &GlobalElementReflectionProvider;
	}
}