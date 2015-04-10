
// include class
#include "SStModuleConfiguration.h"
using namespace Apprentice;
using namespace Environment;

// include SOIA classes
#include "ActivationModule.h"


//////////////////////////////////////////////////////////////
// Init

SStModuleConfiguration::SStModuleConfiguration() : ModuleConfiguration()
{

}
SStModuleConfiguration::~SStModuleConfiguration()
{

}

//////////////////////////////////////////////////////////////
// Events

void SStModuleConfiguration::Handle(const Event &InEvent)
{
	if (InEvent == ActivationModule::ERequest_ActivateNextModules)
	{

	}
}
