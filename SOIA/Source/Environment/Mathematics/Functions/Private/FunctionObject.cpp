
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Functions/Public/FunctionObject.h"
using namespace Environment;

#include "Environment/Mathematics/Runtime/Public/OP_CalculateFunction.h"
#include "Environment/Mathematics/Runtime/Public/Constant.h"

#include <iostream>

FunctionObject::FunctionObject(MathContainer* InRuntime, const Value_ID &InFunction)
{
	MathRuntime = InRuntime;
	Function = InFunction;
	FunctionCall = MathRuntime->DefineValue(new Constant(0));
}

double FunctionObject::get(double x)
{
	double result;
	MathRuntime->RedefineValue(FunctionCall, new OP_CalculateFunction(&MathRuntime->FuncCache, std::vector < Value_ID > {
		Function,
		MathRuntime->DefineValue(new Constant(x)) }));
	std::cout << std::endl << "FunctionObject: New Calculation: X=" << x << std::endl;
	result = MathRuntime->CalculateValue(FunctionCall);
	return result;
}