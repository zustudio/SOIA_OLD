
#include "Definitions.h"

#include "OP_Select.h"
using namespace Environment;

#include <assert.h>

OP_Select::OP_Select(const std::vector<Element_ID> &InOperands) : BaseType(InOperands)
{

}

double OP_Select::Calculate(const std::vector<Value*> &DefinedValues)
{
	Value* op1;
	Value* op2;
	Value* op3;
	FindOperands(DefinedValues, op1, op2, op3);

	double testResult = op1->Calculate(DefinedValues);
	double result;

	if (testResult == 0)
	{
		result = op2->Calculate(DefinedValues);
	}
	else
	{
		result = op3->Calculate(DefinedValues);
	}

	return result;
}