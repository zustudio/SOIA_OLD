
#include "GroupFunc_DataPoints.h"

using namespace IA::MeaningStream;



VectorND<float>* GroupFunc_DataPoints::GetExtend(const std::deque<ExData*> &Occupants)
{
	std::vector<float> result = std::vector<float>();
	result.push_back(Occupants.size());
	result.push_back(1);
	return new VectorND<float>(result);
}