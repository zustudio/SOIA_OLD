
#pragma once

#include <assert.h>
#include <vector>

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
			Lower = InLower;
			Upper = InUpper;
		}
		static Range<T> Empty()
		{
			return Range<T>(0, -1);
		}

		//----- operators -----
		bool operator==(Range<T> const & InOther)
		{
			return Lower == InOther.Lower && Upper == InOther.Upper;
		}

		//----- ranged for loop -----
		class Iterator
		{
		public:
			Iterator(T InT)
				: MyT(InT)
			{}

			bool operator !=(Iterator const & InOtherIterator)
			{
				return MyT != InOtherIterator.MyT;
			}
			Iterator& operator++()
			{
				++MyT;
				return *this;
			}
			T& operator*()
			{
				return MyT;
			}
			operator int()
			{
				return MyT;
			}

		private:
			T MyT;
		};
		Iterator begin()
		{
			return Iterator(Lower);
		}
		Iterator end()
		{
			return Iterator(Upper + 1);
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