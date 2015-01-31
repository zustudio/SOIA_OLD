
#include "MeaningService.h"

#include "GroupCrit_Equal.h"
#include "GroupCrit_Parentage.h"
#include "GroupFunc_DataPoints.h"

using namespace IA;
using namespace IA::MeaningStream;
using namespace SO::MeaningStream;
using namespace SO::Com;

//////////////////////////////////////////////////////////////////////////////////////
// management
MeaningService::MeaningService(ComService* Up) : IIComIO(Up)
{
	DataSets = std::vector < Handle<ExDSet> >();
	RegisteredData = std::deque<ExData*>();
	CurrentEngine = nullptr;
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
	ICom_RegisterCmd(Commands, MeaningService, cmd_info, "info");
	ICom_RegisterCmd(Commands, MeaningService, cmd_addgroup, "addgroup");
	ICom_RegisterCmd(Commands, MeaningService, cmd_convertdata, "convertdata");
	ICom_RegisterCmd(Commands, MeaningService, cmd_interpretdata, "interpretdata");
}
Handle<ICom>& MeaningService::cGetHandle()
{
	TryCreateHandle("MeaningSrvc");
	return IIComIO::cGetHandle();
}

bool MeaningService::cmd_info(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	std::string sets = "Following sets are available:\n\t\t";

	for (auto set : DataSets)
	{
		sets += set.getName();
		sets += " | ";
	}
	cSend("Console", "reply", sets);
	return true;
}

/*	Adds the passed group to named or referenced DataSet
	 @Arg0:	(std::string | Handle<DataSet>)	DataSet to be added to (is created if neccessary).
	 @Arg1: (ExGroup)						Group to be added.
*/
bool MeaningService::cmd_addgroup(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	std::string* set_Name = Args[0].CastTo<std::string>();
	Handle<ExDSet>* set_Handle = Args[0].CastTo<Handle<ExDSet> >();
	ExGroup* group = Args[1].CastTo<ExGroup>();

	ExDSet* set;
	//try to find mentioned set
	if (set_Name)
	{
		set_Handle = new Handle<ExDSet>(nullptr, *set_Name);
	}
	if (set_Handle)
	{
		set = set_Handle->getObj(DataSets);
		set_Name = &set_Handle->getName();
	}
	// if not found, create new one
	if (!set)
	{
		set = new ExDSet(std::deque<ExGroup*>(), &RegisteredData);
		DataSets.push_back(Handle<ExDSet>(set, *set_Name));
	}

	if (group)
	{
		set->AddGroup(group);
	}




/*



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
	}*/
	return true;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cmd FUNCTIONALITY
//-------------------------------------------------------------------------------------------------------------
//    converting
bool MeaningService::cmd_convertdata(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	bool result = false;
	Engine* newEngine = nullptr;
	if (Args.size() >= 1)
	{
		newEngine = Args[0].CastTo<Engine>();
	}
	if (newEngine)
	{
		CurrentEngine = newEngine;
	}
	if (CurrentEngine)
	{
		Convert(CurrentEngine->getDataStart(), 10);
	}
	return result;
}
/** creates ExData for every connected data point of the passed data up to the passed depth*/
ExData* MeaningService::Convert(IData* myData, int Depth)
{
	RegisteredData.clear();
	return exe_Convert(myData, Depth, new std::deque<IData*>());
}
ExData* MeaningService::exe_Convert(IData* Current, int Depth, std::deque<IData*>* Ignore)
{
	if (Depth < 0)
		return nullptr;

	if (std::find(Ignore->begin(), Ignore->end(), Current) != Ignore->end())
		return nullptr;

	ExData* currentObj = new ExData(Current, &RegisteredData);
	RegisteredData.push_back(currentObj);


#if cSO_DebugDE > 1
	cSend("Console", "echo", (checkM(MText) ? *currentObj->getText() : std::to_string(currentObj->CurrentSource->get())) + " in -depth of " + std::to_string(Depth) + '\n');
#endif

	Ignore->push_back(Current);
	Depth -= 1;

	for (int p_Next = 0; p_Next < Current->getConnectedNum(); p_Next++)
	{
		exe_Convert(Current->getConnected(p_Next), Depth, Ignore);
	}

	return currentObj;
}

//-------------------------------------------------------------------------------------------------------------
//     interpreting
bool MeaningService::cmd_interpretdata(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	SetHierarchicBonds(RegisteredData[0]);
	cSend("Console", "echo", "-- parent has " + std::to_string(RegisteredData[0]->Children.size()) + " Children\n");
	CreateAutoGroups();
	//cSend("Console", "echo", "-- created")
	return true;
}
/** First sets the distance of every DE_Objects to the master-parent,
then checks every object for the connected data with the lowest distance
and sets it as parent of the current one
*/
void MeaningService::SetHierarchicBonds(ExData* Current)
{
	//set distances
	exe_SetHierarchicDistances(Current, nullptr, 0);

	//set parents & children
	ExData* nearest;
	ExData* current;
	for (int p_Obj = 0; p_Obj < RegisteredData.size(); p_Obj++)
	{
		current = RegisteredData[p_Obj];


		std::deque<ExData*> connected = *current->getConnected();
		if (connected.size() == 0)
			continue;

		if (current->HierarchicDistance == 0)
		{
			current->Parent = NULL;
			continue;
		}

		nearest = connected[0];

		for (int p_Next = 0; p_Next < connected.size(); p_Next++)
		{
			if (connected[p_Next]->HierarchicDistance < nearest->HierarchicDistance)
				nearest = connected[p_Next];
		}

		current->Parent = nearest;
		nearest->Children.push_back(current);
	}
}

void MeaningService::exe_SetHierarchicDistances(ExData* Current, ExData* Caller, int Distance)
{
	std::deque<ExData*> connected = *Current->getConnected();
	if (Caller)
		connected.erase(std::find(connected.begin(), connected.end(), Caller));

	for (int p_Next = 0; p_Next < connected.size(); p_Next++)
	{
		if (connected[p_Next]->HierarchicDistance >= 0 && connected[p_Next]->HierarchicDistance + 1 <= Distance)
			return;
	}

	Current->HierarchicDistance = Distance;
	for (int p_Next = 0; p_Next < connected.size(); p_Next++)
	{
		exe_SetHierarchicDistances(connected[p_Next], Current, Distance + 1);
	}
}

void MeaningService::CreateAutoGroups()
{
	std::deque<ExGroup*> groups = std::deque<ExGroup*>();
	std::deque<ExData*> owners = std::deque<ExData*>();

	

	for (ExData* data : RegisteredData)
	{
		//create parentage group
		if (data->Children.size() > 0)
		{
			GroupCrit_Parentage* crit = new GroupCrit_Parentage();
			crit->CreateFrom(data);
			groups.push_back(new ExGroup(crit, new GroupFunc_DataPoints()));
			owners.push_back(data);

			cSend("Console", "echo", " -- Added group of: " + *data->getText());
		}
	}
	
	GroupCrit_Equal* crit = new GroupCrit_Equal();
	crit->CreateFrom(RegisteredData[0]);
	groups.push_front(new ExGroup(crit, new GroupFunc_DataPoints()));
	owners.push_front(RegisteredData[0]);

	


	

	ExDSet* newSet = new ExDSet(groups, &RegisteredData);
	newSet->AddToGroups(RegisteredData);
	newSet->Scan();

	for (ExGroup* parentGroup : groups)
	{
		std::deque<ExData*> parents = *parentGroup->GetOccupants(); // = parentGroup->GetBaseData();
		for (ExGroup* childGroup : groups)
		{
			for (ExData* test_Parent : parents)
			{
				if (test_Parent == childGroup->GetBaseData())
					parentGroup->AddChildGroup(childGroup);
			}
		}

	}

	Handle<ExDSet> hndl = Handle<ExDSet>(newSet, "standard");
	DataSets.push_back(hndl);
}