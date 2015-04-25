
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

		//////////////////////////////////////////////////////////////////
		// Variables
		T Lower;
		T Upper;
	};
}