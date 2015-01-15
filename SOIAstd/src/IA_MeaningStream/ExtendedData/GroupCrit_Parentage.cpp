
#include "GroupCrit_Parentage.h"

using namespace IA::MeaningStream;

bool GroupCrit_Parentage::CreateFrom(ExData* NewObligatoryParent)
{
	ObligatoryParent = NewObligatoryParent;
	return true;
}

int GroupCrit_Parentage::Complies(ExData* Test)
{
	float result = 0;
	if (Test->Parent == ObligatoryParent)
	{
		result = 10;
	}
	return result;
}
