// c Maxim Urschumzew
// framework game.cpp file

#include "stdafx.h"
#include "Game.h"

using namespace IA;

//////////////////////////////////////////////////////////////
// game
Data* Game::CalculateResult(Data* Input)
{
	Data* result = new Data();
	result->Content = Input->Content;
	return result;
}

//////////////////////////////////////////////////////////////
// io
Data* Game::IFuncResultOfAction(Data* Input)
{
	return CalculateResult(Input);
}

//////////////////////////////////////////////////////////////
// init
void Game::init()
{

}