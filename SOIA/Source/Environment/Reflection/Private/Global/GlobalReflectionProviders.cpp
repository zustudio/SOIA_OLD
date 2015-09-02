//
#include "Definitions.h"

#include "AtomConverterProvider.h"
#include "RClassProvider.h"
using namespace Environment;

// Global element and atom reflection provider
namespace Environment
{

	AtomConverterProvider CurrentAtomConverterProvider;
	RClassProvider CurrentRClassProvider;
	LIBIMPEXP AtomConverterProvider* GlobalAtomConverterProvider()
	{
		return &CurrentAtomConverterProvider;
	}
	LIBIMPEXP RClassProvider* GlobalRClassProvider()
	{
		return &CurrentRClassProvider;
	}
}