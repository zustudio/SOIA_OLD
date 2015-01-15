
#pragma once

#include "VectorND.h"
#include "IGroupFunction.h"

namespace IA
{
	namespace MeaningStream
	{
		class GroupFunc_DataPoints : public IGroupFunction
		{
			virtual VectorND<float>* GetExtend(const std::deque<ExData*> &Occupants) override;
		};
	}
}