
#pragma once

#include "IDraw.h"

namespace IA
{
	namespace MeaningStream
	{
		class Draw_2D : public IDraw
		{
		public:
			virtual void Draw(CCanvas* Canvas, std::deque<ExGroup*>* Groups) override;
		};
	}
}