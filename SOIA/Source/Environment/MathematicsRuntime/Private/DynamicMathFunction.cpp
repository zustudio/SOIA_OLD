
#include "Definitions.h"

#include "DynamicMathFunction.h"
using namespace Environment;

#include "MathContainer.h"

DynamicMathFunction::DynamicMathFunction(MathContainer * InContainer, Value * InMathObject)
	:
	Container(InContainer),
	MathObject(InMathObject)
{}

double DynamicMathFunction::Execute(std::vector<double> const & InArguments)
{
	return Container->Calculate(MathObject, InArguments);
}
