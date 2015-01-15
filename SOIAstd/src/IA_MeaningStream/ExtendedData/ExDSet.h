#pragma once

#include <deque>

#include "ExData.h"
#include "ExGroup.h"

namespace IA
{
	namespace MeaningStream
	{
		class ExDSet
		{
		private:
			std::deque<ExData*>* AllData;
			std::deque<ExGroup*> Groups;
		public:
			////////////////////////////////////////
			// functions
			//---- init ----
			ExDSet(const std::deque<ExGroup*> &NewGroups, std::deque<ExData*>* AllData);
			//---- runtime grouping ----
			/*Creates data set from the given ExData.
				- ExData must be already parented.*/
			void Scan();
			void AddToGroups(const std::deque<ExData*> &AllData);
			//---- getter / setter ----
			std::deque<ExGroup*>* GetGroups();
		};
	}
}