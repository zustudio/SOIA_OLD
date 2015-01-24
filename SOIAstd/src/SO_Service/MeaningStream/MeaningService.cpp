
#include "MeaningService.h"

using namespace IA::MeaningStream;
using namespace SO::MeaningStream;
using namespace SO::Com;

//////////////////////////////////////////////////////////////////////////////////////
// external executable commands
bool MeaningService::cmd_CreateDSet(const Handle<ICom> &Caller, const std::vector<void*> &Args)
{
	//const Handle<ExDSet> &NewSet
	//DataSets.push_back(NewSet);
	return false;
}
void MeaningService::cmd_AddDGroup(const Handle<ICom> &Caller, const std::vector<void*> &Args)
{
	//Target.getObj(&DataSets)->AddGroup(NewGroup.getObj());
}

//////////////////////////////////////////////////////////////////////////////////////
// management
MeaningService::MeaningService()
{

}
MeaningService::~MeaningService()
{
	for (Handle<ExDSet> set : DataSets)
	{
		delete set.getObj();
	}
}
