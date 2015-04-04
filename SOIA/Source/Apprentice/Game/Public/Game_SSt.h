
#pragma once

#include "Game.h"

namespace IA
{
	class Game_StatedState : public Game
	{
	public:
		//vars
		int LastVisible;
		//game
		Game_StatedState();
		virtual std::vector<int>* CalculateResult(IData* Input) override;
	};
}