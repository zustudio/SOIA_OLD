

#include "Game_SSt.h"

#include "stdafx.h"

using namespace IA;

std::vector<int>* Game_StatedState::CalculateResult(IData* Input)
{
	std::vector<int>* result = new std::vector<int>();
	result->push_back(int(*Input) + 3);
	return result;
}
