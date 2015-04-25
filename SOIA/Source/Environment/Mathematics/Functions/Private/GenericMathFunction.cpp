
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Functions/Public/GenericMathFunction.h"
using namespace Environment;

#include "Environment/Mathematics/Runtime/Public/OP_CalculateFunction.h"
#include "Environment/Mathematics/Runtime/Public/Constant.h"

#include <iostream>

GenericMathFunction::GenericMathFunction(MathContainer* InRuntime, const Element_ID &InFunction)
{
	MathRuntime = InRuntime;
	Function = InFunction;
	FunctionCall = MathRuntime->Register(new Constant(0));
}

double GenericMathFunction::get(double x)
{
	double result;
	MathRuntime->ReRegister(FunctionCall, new OP_CalculateFunction(&MathRuntime->FuncCache, std::vector < Element_ID > {
		Function,
		MathRuntime->Register(new Constant(x)) }));
	std::cout << std::endl << "GenericMathFunction: New Calculation: X=" << x << std::endl;
	result = MathRuntime->CalculateValue(FunctionCall);
	return result;
}