
#pragma once

#include "Environment/Reflection/Atomic/Public/AtomReflection.h"

#include <iostream>
#include <regex>

namespace Environment
{
	class DLLIMPEXP VectorAtomReflection : public AtomReflection
	{
	public:
		virtual bool IsType(const std::string& InTypeName) override;
		
		std::string GetAtomString(VoidPointer& InAtom);
	};
}
