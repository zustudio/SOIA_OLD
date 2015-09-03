
#include "Definitions.h"

#include "OP_CalculateFunction.h"
using namespace Environment;

#include "Constant.h"
#include "Variable.h"
#include "FunctionCache.h"
#include "DefinitionSet.h"

#include <assert.h>
#include <iostream>

OP_CalculateFunction::OP_CalculateFunction(RPointer<Value> InFunctionDefinition, std::vector<RPointer<Value>> const & InParameters)
	: BaseType(InParameters),
	FunctionDefinition(InFunctionDefinition)
{}

void OP_CalculateFunction::ApplyAsSpecialValue(double InResult)
{
	MR_Function* realFunction = dynamic_cast<MR_Function*>(FunctionDefinition.RawPointer());
	std::vector<double> parameterValues;
	parameterValues.reserve(Operands.size());
	if (realFunction)
	{
		DefinitionSet EmptyDefinitionSet;
		// calculate parameters
		for (RPointer<Value> parameter : Operands)
		{
			parameterValues.push_back(parameter->Calculate(&EmptyDefinitionSet));
		}

		realFunction->SetSpecialValue(parameterValues, InResult);
	}
}

double OP_CalculateFunction::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	double result = 0;

	// prepare new set to pass into calculation
	DefinitionSet NewDefinitionsToForward = DefinitionSet();

	// if function is a real function, calculate all function arguments and save them into new definition set
	MR_Function* realFunction = dynamic_cast<MR_Function*>(FunctionDefinition.RawPointer());
	std::vector<double> parameterValues;
	parameterValues.reserve(Operands.size());
	if (realFunction)
	{
		// calculate parameters
		for (RPointer<Value> parameter : Operands)
		{
			parameterValues.push_back(parameter->Calculate(ForwardedDefinitions));
		}

		// try to find cached function call entry
		if (realFunction->GetCachedFunctionCall(parameterValues, result))
			return result;

		// else prepare new definition set for calculation
		int n = parameterValues.size();
		for (int i = 0; i < n; i++)
		{
			NewDefinitionsToForward.Register(
				new Constant(parameterValues[i]),
				realFunction->GenerateParameterName(i));
		}
	}

	// calculate function
	result = FunctionDefinition->Calculate(&NewDefinitionsToForward);

	// cache result if possible
	if (realFunction)
	{
		realFunction->CacheFunctionCall(parameterValues, result);
	}

	return result;
}

void OP_CalculateFunction::PrepareCache()
{
	Super::PrepareCache();
	FunctionDefinition.RecacheTarget();
}
