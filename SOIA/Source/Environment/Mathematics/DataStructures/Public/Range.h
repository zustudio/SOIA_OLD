
#pragma once

#include <assert.h>

namespace Environment
{
	template<typename T>
	class Range
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