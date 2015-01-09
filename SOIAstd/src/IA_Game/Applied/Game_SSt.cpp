

#include "Game_SSt.h"

#include "stdafx.h"

using namespace IA;

Game_StatedState::Game_StatedState()
{
	LastVisible = 0;
}
             
std::vector<int>* Game_StatedState::CalculateResult(IData* Input)
{
	std::vector<int>* result = new std::vector<int>();
	result->push_back(int(*Input) == LastVisible ? 1 : 0);

	float rand = (float)std::rand() / (float)RAND_MAX;
	LastVisible = rand * 4;
	result->push_back(LastVisible);

	return result;
}
