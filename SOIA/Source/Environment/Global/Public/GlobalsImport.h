
#pragma once

#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"
#include "Environment/Reflection/Element/Public/ElementReflectionProvider.h"

namespace Environment
{
	extern DLLIMPEXP AtomReflectionProvider* GetAtomReflectionProvider();
	extern DLLIMPEXP ElementReflectionProvider* GetElementReflectionProvider();
}