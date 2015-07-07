// SOIAme.h
#pragma once

#include <vector>

#include "IData.h"

namespace IA {

	class Game
	{
	public:
		///////////////////////////////////////////////////////////////////////
		// game
		virtual std::vector<int>* CalculateResult(IData* Input);

		///////////////////////////////////////////////////////////////////////
		// io
		std::vector<int>* IFuncResultOfAction(IData* Input);

		///////////////////////////////////////////////////////////////////////
		// init
		virtual void init();
	};
}