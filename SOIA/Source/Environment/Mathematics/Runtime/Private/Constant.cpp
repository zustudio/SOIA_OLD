
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/Constant.h"
using namespace Environment;

Constant::Constant(double InConstant)
{
	myValue = InConstant;
}

double Constant::Calculate(const std::vector<Value*> &InDefinedValues)
{
	return myValue;
}