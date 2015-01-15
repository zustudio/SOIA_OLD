
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
			virtual VectorND<float>* GetExtend(const std::deque<ExData*> &Occupants) = 0;
		};
	}
}