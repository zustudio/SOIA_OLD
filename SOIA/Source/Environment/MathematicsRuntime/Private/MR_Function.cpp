
#include "Definitions.h"

#include "MR_Function.h"

#include "Constant.h"
#include "DefinitionSet.h"

#include <string>

MR_Function::MR_Function(RPointer<Value> InFunctionBody, std::vector<RPointer<Variable>> const & InParameter)
	: BaseType(),
	FunctionBody(InFunctionBody),
	Parameter(InParameter)
{
	for (int index_parameter = 0; index_parameter < Parameter.size(); ++index_parameter)
	{
		RPointer<Variable> parameter = Parameter[index_parameter];
		parameter->MakeFunctionParameter(index_parameter);
	}
}

void MR_Function::SetBody(RPointer<Value> InFunctionBody)
{
	FunctionBody = InFunctionBody;
}

void MR_Function::SetSpecialValue(std::vector<double> InOperands, double InResult)
{
	SpecialValues.CacheFunctionCall(InOperands, InResult);
}

bool MR_Function::GetCachedFunctionCall(std::vector<double> InOperands, double & OutResult)
{
	return SpecialValues.GetCachedFunctionCall(InOperands, OutResult)
		|| Cache.GetCachedFunctionCall(InOperands, OutResult);
}

void MR_Function::CacheFunctionCall(std::vector<double> InOperands, double InResult)
{
	Cache.CacheFunctionCall(InOperands, InResult);
}

double MR_Function::Calculate(DefinitionSet * const & ForwardedDefinitions)
{
	//// rename passed parameters to their real names
	//std::vector<Constant*> passedParameters = ForwardedDefinitions->GetAllElements<Constant>();
	//for (Constant* passedParameter : passedParameters)
	//{
	//	std::string & parameterName = passedParameter->GetName();
	//	std::string parameterName_Function;
	//	int parameterName_Number;
	//	SplitParameterName(parameterName, parameterName_Function, parameterName_Number);

	//	if (parameterName_Function == GetName())
	//	{
	//		parameterName = Parameter[parameterName_Number]->GetName();
	//	}
	//}

	// forward paramters to function definition
	return FunctionBody->Calculate(ForwardedDefinitions);
}

void MR_Function::PrepareCache()
{
	FunctionBody.RecacheTarget();
	for (auto parameter : Parameter)
	{
		parameter.RecacheTarget();
	}
}

std::string MR_Function::GenerateParameterName(int InVariableNum)
{
	return Parameter[InVariableNum]->GetName();
}
//
//void MR_Function::SplitParameterName(std::string const & InName, std::string & OutName, int & OutNumber)
//{
//	for (int index_name = 0; index_name < InName.size(); ++index_name)
//	{
//		if (InName[index_name] == ':')
//		{
//			OutName = InName.substr(0, index_name);
//			int numStart = index_name + 1;
//			int numLength = InName.size() - numStart;
//			OutNumber = std::atoi(InName.substr(numStart, numLength).c_str());
//			break;
//		}
//	}
//}
