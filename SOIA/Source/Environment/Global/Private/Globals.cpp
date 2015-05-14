//
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"
#include "Environment/Reflection/Element/Public/ElementReflectionProvider.h"
using namespace Environment;

// Global element and atom reflection provider
namespace Environment
{
	//TEST
	IsTrue<true>::Yes Bool;
	IsTrue<std::is_integral<int>::value>::Yes Bool2;
	//ENDTEST


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