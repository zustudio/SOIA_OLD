
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/Variable.h"
using namespace Environment;

Variable::Variable(int InCustomID, double InContent)
{
	VariableNumber = InCustomID;
	Content = InContent;
	ID.bIsConstant = false;
}

void Variable::SetID(Value_ID InID)
{
	Value::SetID(InID);
	ID.bIsConstant = false;
	ID.UniqueIdentifier = VariableNumber;
}

double Variable::Calculate(const std::vector<Value*> &InDefinedVariables)
{
	return Content;
}