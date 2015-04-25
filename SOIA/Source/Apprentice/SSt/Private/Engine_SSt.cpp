
#include "Apprentice/Core/Classes/PrivateDefinitions.h"

#include "Apprentice/SSt/Public/Engine_SSt.h"
using namespace Apprentice;
using namespace Environment;

#include <iostream>

Engine_SSt::Engine_SSt(RContainer &InServiceContainer) : Engine(InServiceContainer)
{

}

void Engine_SSt::Init()
{
	std::cout << "Initializing..." << std::endl;
}

void Engine_SSt::Tick()
{
	std::cout << "Tick!" << std::endl;
}
