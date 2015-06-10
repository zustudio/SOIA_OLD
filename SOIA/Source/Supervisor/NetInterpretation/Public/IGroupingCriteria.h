
#pragma once

#include "ExData.h"

namespace IA
{
	namespace MeaningStream
	{
		class IGroupingCriteria
		{
		public:
			/*Tries to copy the right data's properties to this' criterias definition.
				@return: false if not successfull*/
			virtual bool CreateFrom(ExData*) = 0;
			/*Checks, whether another data matches this criterias definition.
				@return: 0 if no match; 1 - 10 if continueously better match*/
			virtual int Complies(ExData*) = 0;
			/*Returns template, form which this criteria was created*/
			virtual ExData* GetBaseData() = 0;
		};
	}
}