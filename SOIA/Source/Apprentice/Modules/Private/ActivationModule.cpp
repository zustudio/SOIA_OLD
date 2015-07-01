
#include "Apprentice/Core/Classes/PrivateDefinitions.h"

// include class
#include "Apprentice/Modules/Public/ActivationModule.h"
using namespace Apprentice;
using namespace Environment;

//////////////////////////////////////////////////////////////
// Init

ActivationModule::ActivationModule() : 
	cmd_Activate(new RFunction<ActivationModule>(this, &ActivationModule::rawcmd_Activate))
{
}
ActivationModule::~ActivationModule()
{

}

bool ActivationModule::rawcmd_Activate()
{
	ERequest_ActivateNextModules.Raise();
	return true;
}