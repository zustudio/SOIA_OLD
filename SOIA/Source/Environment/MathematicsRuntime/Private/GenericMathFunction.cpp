
#include "Definitions.h"

#include "GenericMathFunction.h"
using namespace Environment;

#include "MathContainer.h"
#include "OP_CalculateFunction.h"
#include "Constant.h"

#include <iostream>

GenericMathFunction::GenericMathFunction(MathContainer* InRuntime, const Element_ID &InFunction)
{
	MathRuntime = InRuntime;
	Function = InFunction;
	FunctionCall = MathRuntime->Register(new Constant(0));
	FunctionArgument0 = new Constant(0);
	MathRuntime->Register(FunctionArgument0);
}

double GenericMathFunction::get(double x)
{
	double result;

	FunctionArgument0->myValue = x;
	MathRuntime->ReRegister(FunctionCall, new OP_CalculateFunction(MathRuntime->FuncCache, std::vector < Element_ID > {
		Function,
		FunctionArgument0->GetID() }));
	//std::cout << std::endl << "GenericMathFunction: New Calculation: X=" << x << std::endl;
	result = MathRuntime->CalculateValue(FunctionCall);
	return result;
}
