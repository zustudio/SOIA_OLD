

#include "stdafx.h"
#include "Game_StatedState.h"

using namespace IA;

std::vector<int>* Game_StatedState::CalculateResult(IData* Input)
{
	std::vector<int>* result = new std::vector<int>();
	result->push_back(int(*Input) + 3);
	return result;
}
