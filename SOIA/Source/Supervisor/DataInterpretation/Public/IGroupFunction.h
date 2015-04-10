
#pragma once

#include <vector>
#include <deque>
#include "ExData.h"

namespace IA
{
	namespace MeaningStream
	{
		class IGroupFunction
		{
		public:
			virtual VectorND<float>* GetExtend(const std::deque<VectorND<float>*> &Occupants) = 0;
			virtual VectorND<float>* GetLocation(ExData* target, const std::deque<ExData*> &Occupants) = 0;
			virtual VectorND<float>* GetBaseLocation(ExData* Base, const std::deque<ExData*> &Occupants) = 0;
		};
	}
}