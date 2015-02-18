
#include "Statistics.h"

using namespace SO::Debug;
using namespace SO::Drawing;

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

std::vector<fPoint> Statistics::GetYGraph_Integrated()
{
	std::vector<fPoint> list_points = std::vector<fPoint>();

	float y = 0;
	float x = -1;

	for (float val : Values)
	{
		y += val;
		x++;
		fPoint point = fPoint(x, y);
		list_points.push_back(point);
	}
	return list_points;
}

////////////////////////////////////////////////////////////////
// add data
void Statistics::AddValue(float Val)
{
	Values.push_back(Val);
}