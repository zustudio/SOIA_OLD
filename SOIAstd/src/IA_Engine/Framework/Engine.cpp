//c Maxim Urschumzew
//Base class for different ai engines, to be inherited - provides framework for communication with Game

#include "stdafx.h"
#include "Game.h"
#include "Thread.h"
#include "Engine.h"

using namespace IA;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// init
Engine::Engine(IA::Game* NewGame)
{
	CurrentGame = NewGame;
	Knowledge = new Data(1114);
}
Engine::~Engine()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
// tick
void Engine::Tick()
{
	Data* test;
	test = new IA::Data();
	test->Content = 0;
	IFuncResultOfAction(test)->Content;
}

/////////////////////////////////////////////////////////////////////////////////////////
// rand
int Engine::InfluencedRand(vector<float> &Chances)
{
	float sum;
	vector<float> relativeChances = vector<float>();
	vector<float> chanceDestribution = vector<float>();
	float randomFloat;
	int chosenInt;

	//add elements to arrays
	for (int i = 0; i < Chances.size(); i++)
	{
		relativeChances.push_back(0);
		chanceDestribution.push_back(0);
	}
	////move negative chances up into positive ones
	float smallestChance = 0;
	for (int i = 0; i < Chances.size(); i++)
	{
		smallestChance = smallestChance <= Chances[i]? smallestChance : Chances[i];
	}
	for (int i = 0; i < Chances.size(); i++)
	{
		Chances[i] -= smallestChance;
	}

	//set minimal chance
	for (int i = 0; i < Chances.size(); i++)
	{
		if (Chances[i] < 1)
			Chances[i] = 1;
	}

	//calculate chance destribution
	//sum up all elements of chances
	for (int i = 0; i < Chances.size(); i++)
	{
		sum += Chances[i];
	}
	//divide by sum
	for (int i = 0; i < Chances.size(); i++)
	{
		relativeChances[i] = Chances[i] / sum;
	}
	//add previous chances to current element
	for (int i = 0; i < Chances.size(); i++)
	{
		chanceDestribution[i] += relativeChances[i] + (i > 0 ? chanceDestribution[i - 1] : 0);
	}

	//get a random float
	randomFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	//calculate which possibility was chosen
	for (int i = Chances.size() - 1; i >= 0; i--)
	{
		if (randomFloat <= chanceDestribution[i])
			chosenInt = i;
	}
	return chosenInt;
}


/////////////////////////////////////////////////////////////////////////////////////////
// io
Data* Engine::IFuncResultOfAction(Data* Output)
{
	Data* Result = CurrentGame->IFuncResultOfAction(Output);

	cout << std::to_string(Output->Content);
	cout << "->";
	cout << std::to_string(Result->Content);
	cout << "\n";

	return Result;
}
//Data* Engine::ReadData()
//{
//	Monitor::Enter(Lock);
//	return Knowledge;
//}
//void Engine::StopData()
//{
//	Monitor::Exit(Lock);
//}
