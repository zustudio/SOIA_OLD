
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/Variable.h"
using namespace Environment;

Variable::Variable(int InCustomID, double InContent)
{
	VariableNumber = InCustomID;
	Content = InContent;
	GetID().UniqueIdentifier = VariableNumber;
}

void Variable::SetID(Element_ID InID)
{
	Value::SetID(InID);

	GetID().UniqueIdentifier = VariableNumber;
}

double Variable::Calculate(const std::vector<Value*> &InDefinedVariables)
{
	return Content;
}