
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
	std::string* typeToCreate = Args[0].CastTo<std::string>();
	if (!typeToCreate)
		return false;

	if (*typeToCreate == "set")
	{
		Handle<ExDSet>* setHndl = Args[1].CastTo<Handle<ExDSet> >();
		DataSets.push_back(setHndl->getObj());
	}
	else if (*typeToCreate == "group")
	{
		Handle<ExDSet>* setHndl = Args[1].CastTo<Handle<ExDSet> >();
		if (!setHndl)
		{
			std::string* setName = Args[1].CastTo<std::string>();
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
		Handle<ExGroup>* groupHndl = Args[2].CastTo<Handle<ExGroup> >();
		
		setHndl->getObj()->AddGroup(groupHndl->getObj());
	}
	
}