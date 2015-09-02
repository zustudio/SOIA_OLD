
#include "Definitions.h"

#include "OP_Divide.h"
using namespace Environment;

#include <assert.h>

OP_Divide::OP_Divide(const std::vector<RPointer<Value>> &InOperands) : BaseType(InOperands)
{

}

double OP_Divide::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	double res1 = Operands[0]->Calculate(ForwardedDefinitions);
	double res2 = Operands[1]->Calculate(ForwardedDefinitions);

	return res1 / res2;
}