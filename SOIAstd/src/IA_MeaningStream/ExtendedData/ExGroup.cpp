
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
// encapsuled IGroupFunc functionality
VectorND<float>* ExGroup::GetExtend()
{
	return Function->GetExtend(Occupants);
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
