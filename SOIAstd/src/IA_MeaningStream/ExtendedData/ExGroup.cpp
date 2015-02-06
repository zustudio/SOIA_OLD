
#include "ExGroup.h"

using namespace IA::MeaningStream;

ExGroup::ExGroup(IGroupingCriteria *NewCriteria, IGroupFunction *NewFunction)
{
	Criteria = NewCriteria;
	Function = NewFunction;
}
ExGroup::~ExGroup()
{
}

int ExGroup::TryAdd(ExData* Data)
{
	int compatability = Criteria->Complies(Data);
	if (compatability)
	{
		if (std::find(Occupants.begin(), Occupants.end(), Data) == Occupants.end())		// if not already added
		{
			Occupants.push_back(Data);													// add now
			//std::cout << "    - Added data '" << *Data->getText() << "'\t\tto group of '" << *GetBaseData()->getText() << "'" << std::endl;
		}
	}
	return compatability;
}

bool ExGroup::Remove(ExData* Data)
{
	bool result = false;
	auto index = std::find(Occupants.begin(), Occupants.end(), Data);
	if (index != Occupants.end())
	{
		Occupants.erase(index);
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////
// encapsuled functionality
//---- IGroupFunc ----
VectorND<float>* ExGroup::GetExtend()
{
	std::deque<VectorND<float>*> occExtends = std::deque < VectorND<float>*>();
	std::deque<ExData*> dataToCalcExtendOf = Occupants;

	for (auto occ : Occupants)
	{
		for (auto childGroup : ChildGroups)
		{
			if (childGroup->GetBaseData() == occ)
			{
				occExtends.push_back(childGroup->GetExtend());
				dataToCalcExtendOf.erase(std::find(dataToCalcExtendOf.begin(), dataToCalcExtendOf.end(), occ));
			}
		}
	}
	
	for (auto occ : dataToCalcExtendOf)
	{
		occExtends.push_back(&occ->InterpProps.IntExtend);
	}
	return Function->GetExtend(occExtends);
}
VectorND<float>* ExGroup::GetLocation(ExData* Target)
{
	return Function->GetLocation(Target, Occupants);
}
VectorND<float>* ExGroup::GetBaseLocation()
{
	return Function->GetBaseLocation(Criteria->GetBaseData(), Occupants);
}
//---- IGroupingCriteria ----
ExData* ExGroup::GetBaseData()
{
	return Criteria->GetBaseData();
}



///////////////////////////////////////////////////////////////////////////////
// getter / setter
std::deque<ExData*>* ExGroup::GetOccupants()
{
	return &Occupants;
}
std::deque<ExGroup*>* ExGroup::GetChildGroups()
{
	return &ChildGroups;
}
void ExGroup::AddChildGroup(ExGroup* NewGroup)
{
	if (NewGroup && NewGroup != this)
	{
		ChildGroups.push_back(NewGroup);
	}
}

