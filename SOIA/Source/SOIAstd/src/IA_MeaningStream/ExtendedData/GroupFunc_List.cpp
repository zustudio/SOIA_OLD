
#include "GroupFunc_List.h"



using namespace IA::MeaningStream;



VectorND<float>* GroupFunc_List::GetExtend(const std::deque<VectorND<float>*> &OccupantExtends)
{
	std::vector<float> result = std::vector<float>();
	result.push_back(0);
	result.push_back(0);

	if (OccupantExtends.size() == 0)
	{
		result[0] = 1;
		result[1] = 1;
		return new VectorND<float>(result);
	}
	else
	{

		for (auto extend : OccupantExtends)
		{
			result[0] = std::fmax(result[0], (*extend)[0]);
			//result[1] += (*extend)[1];
			result[1] = 1;
		}
		//result[1]++;
	}
	return new VectorND<float>(result);
}

VectorND<float>* GroupFunc_List::GetLocation(ExData* target, const std::deque<ExData*> &Occupants)
{
	VectorND<float>* result = new VectorND<float>(2);
	ExData* child0 = nullptr;
	int n = 1 + Occupants.size();
	for (int i = 0; i < n; i++)
	{
		ExData* child1 = i < Occupants.size() ? Occupants[i] : nullptr;

		if (child0)
			(*result)[1] -= (0.5F * child0->InterpProps.IntExtend[1]);
		if (child1)
			(*result)[1] -= (0.5F * child1->InterpProps.IntExtend[1]);
		else
			result = new VectorND<float>(std::vector<float>({ child0->InterpProps.IntExtend[0], 0.0F }));

		child0 = child1;

		if (child1 == target)
		{
			break;
		}















		//ExData* child0 = Occupants[i];
		//if (child0 == target)
		//{
		//	break;
		//}
		//ExData* child1 = Occupants[i + 1];

		////prepare vector for addition
		//std::vector<float> step = std::vector<float>();
		//float step0 = child0->InterpProps.IntExtend[0];
		//float step1 = child1->InterpProps.IntExtend[0];
		//step.push_back(0.5F * (step0 + step1));
		//step.push_back(0);

		///*float step0 = child->InterpProps.IntExtend[0];
		//step0 = step0 - (step0 - 1) / 2;
		//step.push_back(step0);
		//step.push_back(0);*/

		//*result += VectorND<float>(step);
	}
	return result;
}

VectorND<float>* GroupFunc_List::GetBaseLocation(ExData* Base, const std::deque<ExData*> &Occupants)
{
	std::vector<float> result = std::vector<float>();

	if (Base)
	{
		result.push_back(-0.75F);
		result.push_back(/*Base->InterpProps.IntExtend[1] + */1);
	}

	return new VectorND<float>(result);
}