
#include "Definitions.h"

#include "OP_GreaterThan.h"
using namespace Environment;

#include <assert.h>

OP_GreaterThan::OP_GreaterThan(const std::vector<RPointer<Value>> &InOperands) : BaseType(InOperands)
{

}

double OP_GreaterThan::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	double res1 = Operands[0]->Calculate(ForwardedDefinitions);
	double res2 = Operands[1]->Calculate(ForwardedDefinitions);

	return (res1 > res2)? 1 : 0;
}