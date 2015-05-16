
#pragma once

#include "Environment/Reflection/Atomic/Public/Atom.h"
#include <assert.h>

namespace Environment
{
	template<typename T>
	class Range : Atom
	{
	public:
		//////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----

		///Constructor
		Range()
		{
			Lower = 0;
			Upper = 0;
		}
		Range(const T& InLower, const T& InUpper)
		{
			assert(InLower <= InUpper);

			Lower = InLower;
			Upper = InUpper;
		}

		/// Serializing
		static std::string ToString(const Range<T>& InObject)
		{
			return std::to_string(InObject.Lower) + "," + std::to_string(InObject.Upper);
		}
		static Range<T> FromString(const std::string& InString)
		{
			auto result = MatchPattern(InString, "(-?[0-9]+),(-?[0-9]+)");
			if (result.size() == 3)
			{
				return Range<T>(std::atoi(result[1].c_str()), std::atoi(result[2].c_str()));
			}
			else
				return Range<T>();
		}

		//----- usage -----

		/// Tests whether number is in range.
		bool IsInRange(const T& InTest)
		{
			return (InTest >= Lower && InTest <= Upper);
		}

		//////////////////////////////////////////////////////////////////
		// Variables
		T Lower;
		T Upper;
	};
}