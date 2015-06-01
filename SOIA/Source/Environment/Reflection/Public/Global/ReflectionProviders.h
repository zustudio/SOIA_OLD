
#pragma once

#include "AtomReflectionProvider.h"
#include "ElementReflectionProvider.h"

namespace Environment
{
	extern LIBIMPEXP AtomReflectionProvider* GetAtomReflectionProvider();
	extern LIBIMPEXP ElementReflectionProvider* GetElementReflectionProvider();
}