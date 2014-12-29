// c Maxim Urschumzew
// framework game.cpp file

#include "stdafx.h"
#include "Game.h"

using namespace IA;

//////////////////////////////////////////////////////////////
// game
std::vector<int>* Game::CalculateResult(IData* Input)
{
	std::vector<int>* result = new std::vector<int>();
	result->push_back(int(*Input));
	return result;
}

//////////////////////////////////////////////////////////////
// io
std::vector<int>* Game::IFuncResultOfAction(IData* Input)
{
	return CalculateResult(Input);
}

//////////////////////////////////////////////////////////////
// init
void Game::init()
{

}