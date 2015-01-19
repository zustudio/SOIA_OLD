
#pragma once

#include <deque>
#include "VectorND.h"
#include "IGroupingCriteria.h"
#include "IGroupFunction.h"
#include "ExData.h"

namespace IA
{
	namespace MeaningStream
	{
		class ExGroup
		{
		public:
			///////////////////////////////////////////////////
			// functions
			//---- init ----
			ExGroup(IGroupingCriteria *NewCriteria, IGroupFunction *NewFunction);
			virtual ~ExGroup();
			//---- occup management ----
			/*Tries to add given data to this group, returns value on how well data met grouping criteria.
				0		no match, not added
				1 - 10	matching value, added
				10		already included*/
			int TryAdd(ExData*);
			/*Removes an item from this group.*/
			bool Remove(ExData*);

			//---- encapsuled 'Interface' functionality ----
			virtual VectorND<float>* GetExtend();
			VectorND<float>* GetLocation(ExData* Target);
			VectorND<float>* GetBaseLocation();
			ExData* ExGroup::GetBaseData();

			//---- getter / setter ----
			std::deque<ExData*>* GetOccupants();
			std::deque<ExGroup*>* GetChildGroups();
			void AddChildGroup(ExGroup*);

			///////////////////////////////////////////////////
			// variables
		private:
			std::deque<ExData*> Occupants;
			std::deque<ExGroup*> ChildGroups;
			IGroupingCriteria* Criteria;
			IGroupFunction* Function;
		};
	}
}
