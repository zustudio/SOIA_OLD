
#include "Definitions.h"

#include "OP_Substract.h"
using namespace Environment;


OP_Substract::OP_Substract(const std::vector<RPointer<Value>> &InOperands)
{
	Operands = InOperands;
}

double OP_Substract::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	double res1 = Operands[0]->Calculate(ForwardedDefinitions);
	double res2 = Operands[1]->Calculate(ForwardedDefinitions);

	return res1 - res2;
}
