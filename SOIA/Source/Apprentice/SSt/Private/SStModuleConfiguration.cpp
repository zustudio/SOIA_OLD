
#include "Apprentice/Core/Classes/PrivateDefinitions.h"

// include class
#include "Apprentice/SSt/Public/SStModuleConfiguration.h"
using namespace Apprentice;
using namespace Environment;

// include SOIA classes
#include "Apprentice/Modules/Public/ActivationModule.h"

#include <iostream>

//////////////////////////////////////////////////////////////
// Init

SStModuleConfiguration::SStModuleConfiguration()
{
	MyActivationModule.ERequest_ActivateNextModules.AddHandlerFunction(new RFunction<SStModuleConfiguration, EventDetails*>(this, &SStModuleConfiguration::eventhandler_RequestActivateNextModules));
	MyActivationModule.cmd_Activate->Execute({});

}
SStModuleConfiguration::~SStModuleConfiguration()
{

}

//////////////////////////////////////////////////////////////
// Event handlers
bool SStModuleConfiguration::eventhandler_RequestActivateNextModules(Environment::EventDetails*)
{
	std::cout << "Activating next modules..." << std::endl;
	return true;
}
