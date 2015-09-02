
#include "Definitions.h"

#include "Variable.h"
using namespace Environment;

#include "Constant.h"
#include "DefinitionSet.h"
#include "GlobalLogger.h"

Variable::Variable()
	:
	Mode(EVariableMode::Constant),
	ConstantValue(0.0),
	ParameterNumber(0)
{}

void Variable::MakeConstant(double InConstantValue)
{
	Mode = EVariableMode::Constant;
	ConstantValue = InConstantValue;
	ParameterNumber = 0;
}

void Variable::MakeFunctionParameter(int InParameterNumber)
{
	Mode = EVariableMode::FunctionParameter;
	ParameterNumber = InParameterNumber;
	ConstantValue = 0.0;
}

double Variable::Calculate(DefinitionSet* const & ForwardedDefinitions)
{
	double result = 0;

	switch (Mode)
	{
	case Environment::EVariableMode::FunctionParameter:
	{
		Constant* forwardDefinedConstant = ForwardedDefinitions->GetElement<Constant>(GetName());
		if (forwardDefinedConstant)
			result = forwardDefinedConstant->myValue;
		else
			LOG("Variable '" + GetName() + "' could not be calculated because it's value was not forwarded to it", Logger::Severity::Error);
		break;
	}
	case Environment::EVariableMode::Constant:
	{
		result = ConstantValue;
		break;
	}
	default:
		break;
	}

	return result;
}

