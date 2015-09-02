
#include "Definitions.h"

#include "OP_If.h"
using namespace Environment;

#include <assert.h>

OP_If::OP_If(const std::vector<RPointer<Value>> &InOperands) : BaseType(InOperands)
{

}

double OP_If::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	double testResult = Operands[0]->Calculate(ForwardedDefinitions);
	double result;

	if (testResult <= 0)
	{
		result = Operands[1]->Calculate(ForwardedDefinitions);
	}
	else
	{
		result = Operands[2]->Calculate(ForwardedDefinitions);
	}

	return result;
}