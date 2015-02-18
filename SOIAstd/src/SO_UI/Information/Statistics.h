
#pragma once

//properties
#include <vector>

namespace SO
{
	namespace Debug
	{
		enum EValueAttribute
		{

			all = -1,
			Positive = -2,
			Negative = -3,
			Zero = 0,
		};

		class Statistics
		{
		public:
			////////////////////////////////////////////
			// functions
			//---- init ----
			Statistics();

			//---- get statistics ----
			// Returns number of elements with matching attribute.
			int GetNum(EValueAttribute attribute = EValueAttribute::all);
			int GetNum(float Equal);

			//---- set values ---
			// Adds new value.
			void AddValue(float Val);

			////////////////////////////////////////////
			// data to get statistics about
		private:
			std::vector<float> Values;
		};
	}
}