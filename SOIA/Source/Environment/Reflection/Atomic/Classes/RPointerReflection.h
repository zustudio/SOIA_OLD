
#pragma once

#include "Environment/Reflection/Atomic/Public/AtomReflection.h"

namespace Environment
{
	class DLLIMPEXP RPointerReflection : public AtomReflection
	{
		virtual bool IsType(const std::string& InTypeID) override;
		virtual VoidPointer* StringToObject(const std::string& InString) override;
		virtual std::string ObjectToString(VoidPointer& InObject) override;
	};
}