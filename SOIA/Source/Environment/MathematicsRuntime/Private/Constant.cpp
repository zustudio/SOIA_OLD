
#include "Definitions.h"

#include "Constant.h"
using namespace Environment;


Constant::Constant(double InConstant)
{
	myValue = InConstant;
}

double Constant::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	return myValue;
}
