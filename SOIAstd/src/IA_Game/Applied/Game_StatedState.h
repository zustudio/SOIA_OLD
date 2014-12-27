
#pragma once

#include "Game.h"

namespace IA
{
	class Data_StatedState;

	class Game_StatedState : public Game
	{
	public:
		virtual Data_StatedState* CalculateResult(Data_StatedState* Input);
		virtual Data_StatedState* IFuncResultOfAction(Data_StatedState* Input);
	};
}