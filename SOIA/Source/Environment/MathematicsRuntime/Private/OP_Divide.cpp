
#include "Definitions.h"

#include "OP_Divide.h"
using namespace Environment;

#include <assert.h>

OP_Divide::OP_Divide(const std::vector<Element_ID> &InOperands) : BaseType(InOperands)
{

}

double OP_Divide::Calculate(const std::vector<Value*> &DefinedValues)
{
	Value* op1;
	Value* op2;
	Value* op3;
	FindOperands(DefinedValues, op1, op2, op3);

	double res1 = op1->Calculate(DefinedValues);
	double res2 = op2->Calculate(DefinedValues);

	return res1 / res2;
}