
#include "Definitions.h"

#include "Variable.h"
using namespace Environment;

Variable::Variable(int InCustomID, double InContent)
{
	VariableNumber = InCustomID;
	Content = InContent;
	GetID().UniqueIdentifier = VariableNumber;
}

void Variable::SetID(ElementID InID)
{
	Value::SetID(InID);

	GetID().UniqueIdentifier = VariableNumber;
}

double Variable::Calculate(const std::vector<Value*> &InDefinedVariables)
{
	return Content;
}