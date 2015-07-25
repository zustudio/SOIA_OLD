
#pragma once

#include "ExData.h"

#include "IGroupingCriteria.h"

namespace IA
{
	namespace MeaningStream
	{
		class GroupCrit_Parentage : public IGroupingCriteria
		{
		private:
			//---- criteria ----
			ExData* ObligatoryParent;
		public:
			//---- override ----
			virtual bool CreateFrom(ExData* NewObligatoryParent) override;
			virtual int Complies(ExData* Test) override;
			virtual ExData* GetBaseData() override;
		};
	}
}