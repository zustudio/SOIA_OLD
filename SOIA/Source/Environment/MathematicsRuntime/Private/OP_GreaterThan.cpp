
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/OP_GreaterThan.h"
using namespace Environment;

#include <assert.h>

OP_GreaterThan::OP_GreaterThan(const std::vector<Element_ID> &InOperands) : BaseType(InOperands)
{

}

double OP_GreaterThan::Calculate(const std::vector<Value*> &DefinedValues)
{
	Value* op1;
	Value* op2;
	Value* op3;
	FindOperands(DefinedValues, op1, op2, op3);

	double res1 = op1->Calculate(DefinedValues);
	double res2 = op2->Calculate(DefinedValues);

	return (res1 > res2)? 1 : 0;
}