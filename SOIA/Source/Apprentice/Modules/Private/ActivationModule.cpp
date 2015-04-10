
// include class
#include "ActivationModule.h"
using namespace Apprentice;
using namespace Environment;

//////////////////////////////////////////////////////////////
// Init

ActivationModule::ActivationModule()
{
	RaiseEvent(ERequest_ActivateNextModules);
}
ActivationModule::~ActivationModule()
{

}
