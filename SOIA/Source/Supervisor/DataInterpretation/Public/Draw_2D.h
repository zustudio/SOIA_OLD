
#pragma once

//super classes
#include "IDraw.h"
#include "IIDebuggable.h"

namespace IA
{
	namespace MeaningStream
	{
		class Draw_2D : public IDraw, protected SO::Debug::IIDebuggable
		{
		public:
			Draw_2D(SO::Com::ComService* NewUp);

			virtual void Draw(CCanvas* Canvas, std::deque<ExGroup*>* Groups) override;
			void exe_SetLocation(ExGroup* Group, VectorND<float> &StartLoc, VectorND<float> &IntLocation);

			virtual Handle<ICom>& cGetHandle() override;
		};
	}
}