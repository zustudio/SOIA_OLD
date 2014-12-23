
#pragma once
#include "stdafx.h"

#include "Data.h"
#include "Data_StatedState.h"


namespace IA
{
	namespace MeaningStream
	{
		class ExData : public cIA_Data
		{
		public:
			///////////////////////////////////////////////////
			// vars
			cIA_Data* CurrentSource;
			std::deque<ExData*>* CurrentAllObjects;

			int HierarchicDistance;
			ExData* Parent;
			std::deque<ExData*> Children;
			fPoint Location;
			fPoint Extend;

			///////////////////////////////////////////////////
			// functions
			ExData(cIA_Data* NewSource, std::deque<ExData*> *AllObjects);
			std::deque<ExData*>* getConnected(Data_StatedState::LinkType ConnectionType);
		};
	}
}
