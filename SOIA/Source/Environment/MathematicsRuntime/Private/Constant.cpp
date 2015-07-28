
#include "Definitions.h"

#include "Constant.h"
using namespace Environment;


Constant::Constant(double InConstant)
{
	myValue = InConstant;
}

double Constant::Calculate(const std::vector<Value*> &InDefinedValues)
{
	return myValue;
}
