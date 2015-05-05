
#pragma once

#include <string>

namespace Environment
{
	class RElement;
	class DLLIMPEXP RClass
	{
	public:
		virtual RElement* GetDefaultObject() = 0;
		virtual std::string GetType() = 0;
		virtual bool IsType(const std::string& InTypeID) = 0;
	};
}