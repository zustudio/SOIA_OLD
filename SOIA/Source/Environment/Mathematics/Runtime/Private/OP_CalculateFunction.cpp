
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/OP_CalculateFunction.h"
using namespace Environment;

#include "Environment/Mathematics/Runtime/Public/Variable.h"
#include "Environment/Mathematics/Runtime/Public/FunctionCache.h"

#include <assert.h>
#include <iostream>

OP_CalculateFunction::OP_CalculateFunction(FunctionCache *InFuncCache, const std::vector<Element_ID> &InOperands) : Operation(InOperands)
{
	FuncCache = InFuncCache;
}

double OP_CalculateFunction::Calculate(const std::vector<Value*> &DefinedValues)
{
	Value* op0;
	Value* op1;
	Value* op2;
	FindOperands(DefinedValues, op0, op1, op2);
	

	// clear my values of any variables (not constantly defined or operators) and add my second operand as new variable
	std::vector<Value*> ValuesToPassOn;
	for (Value* value : DefinedValues)
	{
		if (! dynamic_cast<Variable*>(value))
		{
			ValuesToPassOn.push_back(value);
		}
	}
	double rVariable0 = op1->Calculate(DefinedValues);
	Variable* Variable0 = new Variable(0, rVariable0);
	ValuesToPassOn.push_back(Variable0);

	// try get result from func cache, if not available calculate it
	double result;
	if (! FuncCache->GetCachedFunctionCall(op0->GetID(), rVariable0, result))
	{
		result = op0->Calculate(ValuesToPassOn);
		FuncCache->CacheFunctionCall(op0->GetID(), rVariable0, result);
	}

	std::cout << "OP_CalcFunc: " << op0->GetID().Name << "( " << rVariable0 << " ) = ";
	std::cout << result << std::endl;

	return result;
}