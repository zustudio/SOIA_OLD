
#include "Definitions.h"

#include "OP_If.h"
using namespace Environment;

#include <assert.h>

OP_If::OP_If(const std::vector<Element_ID> &InOperands) : BaseType(InOperands)
{

}

double OP_If::Calculate(const std::vector<Value*> &DefinedValues)
{
	Value* op1;
	Value* op2;
	Value* op3;
	FindOperands(DefinedValues, op1, op2, op3);

	double testResult = op1->Calculate(DefinedValues);
	double result;

	if (testResult <= 0)
	{
		result = op2->Calculate(DefinedValues);
	}
	else
	{
		result = op3->Calculate(DefinedValues);
	}

	return result;
}