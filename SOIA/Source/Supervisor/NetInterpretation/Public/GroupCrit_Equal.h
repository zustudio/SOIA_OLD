
#pragma once

#include "ExData.h"

#include "IGroupingCriteria.h"

namespace IA
{
	namespace MeaningStream
	{
		class GroupCrit_Equal : public IGroupingCriteria
		{
		private:
			//---- criteria ----
			ExData* EqualData;
		public:
			//---- override ----
			virtual bool CreateFrom(ExData* NewData) override;
			virtual int Complies(ExData* Test) override;
			virtual ExData* GetBaseData() override;
		};
	}
}