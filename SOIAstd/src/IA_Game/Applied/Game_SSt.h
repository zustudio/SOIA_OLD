
#pragma once

#include "Game.h"

namespace IA
{
	class Game_StatedState : public Game
	{
	public:
		virtual std::vector<int>* CalculateResult(IData* Input) override;
	};
}