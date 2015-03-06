
#pragma once

#include "IGroupFunction.h"
#include "ExGroup.h"
#include "ExData.h"

#include "CCanvas.h"

namespace IA
{
	namespace MeaningStream
	{
		class IDraw
		{
		public:
			/////////////////////////////////////////////////////////////////////////////
			// functions
			//---- draw ----
			virtual void Draw(CCanvas* Canvas, std::deque<ExGroup*>* Groups) = 0;
		};
	}
}