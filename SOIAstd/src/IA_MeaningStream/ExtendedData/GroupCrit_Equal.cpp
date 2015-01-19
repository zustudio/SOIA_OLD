
#include "GroupCrit_Equal.h"

using namespace IA::MeaningStream;

bool GroupCrit_Equal::CreateFrom(ExData* NewData)
{
	EqualData = NewData;
	return true;
}

ExData* GroupCrit_Equal::GetBaseData()
{
	return EqualData;
}

int GroupCrit_Equal::Complies(ExData* Test)
{
	float result = 0;
	if (Test == EqualData)
	{
		result = 10;
	}
	return result;
}
