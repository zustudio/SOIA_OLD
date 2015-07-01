
#include "Apprentice/Core/Classes/PrivateDefinitions.h"

#include "Apprentice/Core/Public/Engine.h"
using namespace Apprentice;
using namespace Environment;

Engine::Engine(Environment::RContainer& InServiceContainer) : RApplication(InServiceContainer)
{
	LeftTickNum = 0;
	auto function = Register(new RFunction<Engine, int>(this, &Engine::cmd_Add), "add");
	GetElement<RFunction<Engine, int> >(function)->Execute(5);
}

void Engine::Main()
{
	Init();

	while (true)
	{
		while (LeftTickNum)
		{
			Tick();
			LeftTickNum--;
		}
		Sleep();
	}
}

////////////////////////////////////////////////////////////////
// Registered Functions
bool Engine::cmd_Add(const int Number)
{
	LeftTickNum += Number;
	WakeUp();
	return true;
}