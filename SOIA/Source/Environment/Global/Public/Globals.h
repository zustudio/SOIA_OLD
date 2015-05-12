
#pragma once

#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"
#include "Environment/Reflection/Element/Public/ElementReflectionProvider.h"

namespace Environment
{
	DLLIMPEXP extern AtomReflectionProvider* GetAtomReflectionProvider();
	DLLIMPEXP extern ElementReflectionProvider* GetElementReflectionProvider();
}