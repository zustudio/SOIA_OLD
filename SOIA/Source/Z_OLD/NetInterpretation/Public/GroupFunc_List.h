
#pragma once

#include "VectorND.h"
#include "IGroupFunction.h"

namespace IA
{
	namespace MeaningStream
	{
		class GroupFunc_List : public IGroupFunction
		{
			virtual VectorND<float>* GetExtend(const std::deque<VectorND<float>*> &Occupants) override;
			virtual VectorND<float>* GetLocation(ExData* target, const std::deque<ExData*> &Occupants) override;
			virtual VectorND<float>* GetBaseLocation(ExData* Base, const std::deque<ExData*> &Occupants) override;
		};
	}
}