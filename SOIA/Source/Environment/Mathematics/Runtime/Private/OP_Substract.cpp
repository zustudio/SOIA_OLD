
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/OP_Substract.h"
using namespace Environment;

#include <assert.h>

OP_Substract::OP_Substract(const std::vector<Element_ID> &InOperands) : Operation(InOperands)
{

}

double OP_Substract::Calculate(const std::vector<Value*> &DefinedValues)
{
	Value* op1;
	Value* op2;
	Value* op3;
	FindOperands(DefinedValues, op1, op2, op3);

	double res1 = op1->Calculate(DefinedValues);
	double res2 = op2->Calculate(DefinedValues);

	return res1 - res2;
}