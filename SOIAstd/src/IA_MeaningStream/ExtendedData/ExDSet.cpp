#include "ExDSet.h"

using namespace IA::MeaningStream;

ExDSet::ExDSet(const std::deque<ExGroup*> &NewGroups, std::deque<ExData*>* NewAllData)
{
	Groups = NewGroups;
	AllData = NewAllData;
}

///////////////////////////////////////////////////////////////////////////////////
// group managment
void ExDSet::AddGroup(ExGroup* NewGroup)
{
	Groups.push_back(NewGroup);
}

///////////////////////////////////////////////////////////////////////////////////
// runtime grouping

void ExDSet::Scan()
{
	AddToGroups(*AllData);
}

void ExDSet::AddToGroups(const std::deque<ExData*> &AllData)
{
	std::cout << "[DATASET]: " << std::endl;
	for (ExData* data : AllData)
	{
		ExGroup* foundGroup = nullptr;
		int val_foundGroup = 0;

		for (ExGroup* group : Groups)
		{
			int val_newFoundGroup = group->TryAdd(data);

			if (foundGroup)
			{
				if (val_foundGroup > val_newFoundGroup)				// remove item again, if an already found group is a better match
				{
					group->Remove(data);
				}
				else
				{
					foundGroup->Remove(data);
				}
			}

			foundGroup = group;
			val_foundGroup = val_newFoundGroup;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
// getter / setter
std::deque<ExGroup*>* ExDSet::GetGroups()
{
	return &Groups;
}
