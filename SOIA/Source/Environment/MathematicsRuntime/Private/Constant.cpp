
#include "Definitions.h"

#include "Constant.h"
using namespace Environment;


Constant::Constant(double InConstant)
{
	myValue = InConstant;
	Next = nullptr;

	Reflect(myValue, Next);
}

double Constant::Calculate(const std::vector<Value*> &InDefinedValues)
{
	return myValue;
}
