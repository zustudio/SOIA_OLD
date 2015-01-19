
#include "GroupFunc_DataPoints.h"



using namespace IA::MeaningStream;



VectorND<float>* GroupFunc_DataPoints::GetExtend(const std::deque<ExData*> &Occupants)
{
	std::vector<float> result = std::vector<float>();
	result.push_back(Occupants.size());
	result.push_back(1);
	return new VectorND<float>(result);
}

VectorND<float>* GroupFunc_DataPoints::GetLocation(ExData* target, const std::deque<ExData*> &Occupants)
{
	VectorND<float>* result = new VectorND<float>(2);
	int n = Occupants.size();
	for (int i = 0; i + 1 < n; i++)
	{
		ExData* child0 = Occupants[i];
		if (child0 == target)
		{
			break;
		}
		ExData* child1 = Occupants[i + 1];

		//prepare vector for addition
		std::vector<float> step = std::vector<float>();
		float step0 = child0->InterpProps.IntExtend[0];
		float step1 = child1->InterpProps.IntExtend[0];
		step.push_back(0.5F * (step0 + step1));
		step.push_back(0);

		/*float step0 = child->InterpProps.IntExtend[0];
		step0 = step0 - (step0 - 1) / 2;
		step.push_back(step0);
		step.push_back(0);*/

		*result += VectorND<float>(step);
	}
	return result;
}

VectorND<float>* GroupFunc_DataPoints::GetBaseLocation(ExData* Base, const std::deque<ExData*> &Occupants)
{
	std::vector<float> result = std::vector<float>();

	if (Base)
	{
		result.push_back(Base->InterpProps.IntExtend[0] / 2);
		result.push_back(Base->InterpProps.IntExtend[1]);
	}

	return new VectorND<float>(result);
}