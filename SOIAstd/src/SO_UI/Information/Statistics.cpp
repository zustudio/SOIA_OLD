
#include "Statistics.h"

using namespace SO::Debug;

//////////////////////////////////////////////////////
// init
Statistics::Statistics()
{
	Values = std::vector<float>();
}

//////////////////////////////////////////////////////
// get attributes
int Statistics::GetNum(EValueAttribute Attribute)
{
	switch (Attribute)
	{
		case EValueAttribute::all:
			return Values.size();
		default:
		{
			int num = 0;
			for (float a : Values)
			{
				if (a == 0 && Attribute == Zero)
					num++;
				else if (a > 0 && Attribute == Positive)
					num++;
				else if (a < 0 && Attribute == Negative)
					num++;
			}
			return num;
		}
	}
}

int Statistics::GetNum(float Equal)
{
	int num = 0;
	for (float a : Values)
	{
		if (a == Equal)
			num++;
	}
	return num;
}

////////////////////////////////////////////////////////////////
// add data
void Statistics::AddValue(float Val)
{
	Values.push_back(Val);
}