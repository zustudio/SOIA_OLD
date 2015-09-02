
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

double OP_CalculateFunction::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	// prepare new set to pass into calculation
	DefinitionSet NewDefinitionsToForward = DefinitionSet();

	// if function is a real function, calculate all function arguments and save them into new definition set
	MR_Function* realFunction = dynamic_cast<MR_Function*>(FunctionDefinition.RawPointer());
	if (realFunction)
	{
		for (int index_argument = 0; index_argument < Operands.size(); index_argument++)
		{
			NewDefinitionsToForward.Register(
				new Constant(Operands[index_argument]->Calculate(ForwardedDefinitions)),
				realFunction->GenerateParameterName(index_argument));
		}
	}

	// calculate function
	return FunctionDefinition->Calculate(&NewDefinitionsToForward);
}

void OP_CalculateFunction::PrepareCache()
{
	Super::PrepareCache();
	FunctionDefinition.RecacheTarget();
}
