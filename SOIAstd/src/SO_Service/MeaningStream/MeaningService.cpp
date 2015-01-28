
#include "MeaningService.h"

using namespace IA::MeaningStream;
using namespace SO::MeaningStream;
using namespace SO::Com;

//////////////////////////////////////////////////////////////////////////////////////
// management
MeaningService::MeaningService(ComService* Up) : IIComIO(Up)
{

}
MeaningService::~MeaningService()
{
	for (Handle<ExDSet> set : DataSets)
	{
		delete set.getObj();
	}
}
//////////////////////////////////////////////////////////////////////////////////////
// ICom
void MeaningService::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	ICom_RegisterCmd(Commands, MeaningService, cmd_create, "create");
}
Handle<ICom>& MeaningService::cGetHandle()
{
	TryCreateHandle("MeaningS");
	return IIComIO::cGetHandle();
}

bool MeaningService::cmd_create(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	ICom_GetSingleArg(std::string, typeToCreate, Args, 0, true);

	if (*typeToCreate == "set")
	{
		ICom_GetSingleArg(Handle<ExDSet>, setHndl, Args, 1, true);
		DataSets.push_back(setHndl->getObj());
	}
	else if (*typeToCreate == "group")
	{
		ICom_GetSingleArg(Handle<ExDSet>, setHndl, Args, 1, false)
		if (!setHndl)
		{
			ICom_GetSingleArg(std::string, setName, Args, 1, false);
			if (setName)
			{
				Handle<ExDSet> tempHndl = Handle<ExDSet>(nullptr, *setName);
				setHndl = new Handle<ExDSet>(tempHndl.getObj(DataSets), *setName);
				if (!setHndl)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		ICom_GetSingleArg(Handle<ExGroup>, groupHndl, Args, 2, true);
		
		setHndl->getObj()->AddGroup(groupHndl->getObj());
	}
	
}