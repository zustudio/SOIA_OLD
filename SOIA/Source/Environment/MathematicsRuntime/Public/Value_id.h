
#pragma once

#include <string>

namespace Environment
{
	class DLLIMPEXP Value_ID
	{
	public:
		Value_ID();
		bool operator == (const Value_ID &other) const;


		int UniqueIdentifier;
		bool bIsConstant;
		std::string name;
	};
}