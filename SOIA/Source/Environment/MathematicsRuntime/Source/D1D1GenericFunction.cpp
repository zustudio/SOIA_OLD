
#include "Definitions.h"

#include "D1D1GenericFunction.h"
using namespace Environment;

#include "MathContainer.h"
#include "OP_CalculateFunction.h"
#include "Constant.h"

#include <iostream>

D1D1GenericFunction::D1D1GenericFunction(MathContainer* InRuntime, const ElementID &InFunction)
{
	MathRuntime = InRuntime;
	Function = InFunction;
	FunctionCall = MathRuntime->Register(new Constant(0));
	FunctionArgument0 = new Constant(0);
	MathRuntime->Register(FunctionArgument0);
}

double D1D1GenericFunction::Calculate(double x)
{
	double result;

	FunctionArgument0->myValue = x;
	MathRuntime->ReRegister(FunctionCall, new OP_CalculateFunction(MathRuntime->FuncCache, std::vector < ElementID > {
		Function,
		FunctionArgument0->GetID() }));
	//std::cout << std::endl << "D1D1GenericFunction: New Calculation: X=" << x << std::endl;
	result = MathRuntime->CalculateValue(FunctionCall);
	return result;
}

ElementID D1D1GenericFunction::GetFunctionID()
{
	return Function;
}
