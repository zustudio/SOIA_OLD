//c Maxim Urschumzew
//Base class for different ai engines, to be inherited - provides framework for communication with Game

#include "stdafx.h"
#include "Game.h"
#include "Engine.h"

using namespace IA;

/////////////////////////////////////////////////////////////////////////////////////////
// init
Engine::Engine(IA::Game^ NewGame)
{
	CurrentGame = NewGame;
}

/////////////////////////////////////////////////////////////////////////////////////////
// main
void Engine::Start()
{
	while (!aAI_Exit)
	{
		if (aAI_LoopsToDo > 0)
		{
			Tick();
			aAI_LoopsToDo--;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// tick
void Engine::Tick()
{
	Data* test;
	test = new IA::Data();
	test->Content = 0;
	System::Console::WriteLine(IFuncResultOfAction(test)->Content);
}


/////////////////////////////////////////////////////////////////////////////////////////
// rand
int Engine::InfluencedRand(Collections::Generic::List<float>^ Chances)
{
	float sum;
	List<float>^ relativeChances = gcnew List<float>();
	List<float>^ chanceDestribution = gcnew List<float>();
	float randomFloat;
	int chosenInt;

	//add elements to arrays
	for (int i = 0; i < Chances->Count; i++)
	{
		relativeChances->Add(0);
		chanceDestribution->Add(0);
	}
	////move negative chances up into positive ones
	float smallestChance = 0;
	for (int i = 0; i < Chances->Count; i++)
	{
		smallestChance = Math::Min(smallestChance, Chances[i]);
	}
	for (int i = 0; i < Chances->Count; i++)
	{
		Chances[i] -= smallestChance;
	}

	//set minimal chance
	for (int i = 0; i < Chances->Count; i++)
	{
		if (Chances[i] < 1)
			Chances[i] = 1;
	}

	//calculate chance destribution
	//sum up all elements of chances
	for (int i = 0; i < Chances->Count; i++)
	{
		sum += Chances[i];
	}
	//divide by sum
	for (int i = 0; i < Chances->Count; i++)
	{
		relativeChances[i] = Chances[i] / sum;
	}
	//add previous chances to current element
	for (int i = 0; i < Chances->Count; i++)
	{
		chanceDestribution[i] += relativeChances[i] + (i > 0 ? chanceDestribution[i - 1] : 0);
	}

	//get a random float
	randomFloat = (float)Generator->NextDouble();

	//calculate which possibility was chosen
	for (int i = Chances->Count - 1; i >= 0; i--)
	{
		if (randomFloat <= chanceDestribution[i])
			chosenInt = i;
	}
	return chosenInt;
}

int Engine::InfluencedRand(array<float>^ Chances)
{
	List<float>^ ListChances = gcnew List<float>();
	for (int i = 0; i < Chances->Length; i++)
	{
		ListChances->Add(Chances[i]);
	}
	return InfluencedRand(ListChances);
}

/////////////////////////////////////////////////////////////////////////////////////////
// multi threading
void Engine::MTAddTicks(int i)
{
	aAI_LoopsToDo += i;
}

/////////////////////////////////////////////////////////////////////////////////////////
// io
Data* Engine::IFuncResultOfAction(Data* Output)
{
	Data* Result = CurrentGame->IFuncResultOfAction(Output);

	System::Console::Write(Output->Content.ToString());
	System::Console::Write("->");
	System::Console::Write(Result->Content.ToString());
	System::Console::Write("\n");

	return Result;
}
Data* Engine::ReadData()
{
	Monitor::Enter(Lock);
	return Knowledge;
}
void Engine::StopData()
{
	Monitor::Exit(Lock);
}
