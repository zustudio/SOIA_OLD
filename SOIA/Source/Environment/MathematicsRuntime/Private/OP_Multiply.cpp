
#include "Definitions.h"

#include "OP_Multiply.h"
using namespace Environment;

#include <assert.h>

OP_Multiply::OP_Multiply(const std::vector<RPointer<Value>> &InOperands) : BaseType(InOperands)
{

}

double OP_Multiply::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	
	double res1 = Operands[0]->Calculate(ForwardedDefinitions);
	double res2 = Operands[1]->Calculate(ForwardedDefinitions);

	return res1 * res2;
}