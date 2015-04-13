
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/MathContainer.h"
using namespace Environment;

MathContainer::MathContainer()
{
	FreeID = Value_ID();
	FreeID.UniqueIdentifier = 1000;
	FuncCache = FunctionCache();
}

Value_ID& MathContainer::DefineValue(Value* InValue)
{
	InValue->SetID(FreeID);
	FreeID.UniqueIdentifier++;

	DefinedValues.push_back(InValue);

	return InValue->ID;
}
Value_ID MathContainer::RedefineValue(const Value_ID& InChangingID, Value* InNewValue)
{
	int n = DefinedValues.size();
	for (int i = 0; i < n; i++)
	{
		if (DefinedValues[i]->ID == InChangingID)
		{
			InNewValue->SetID(InChangingID);
			DefinedValues[i] = InNewValue;
			break;
		}
	}
	Value_ID res = InChangingID;
	return res;
}

double MathContainer::CalculateValue(const Value_ID &InID)
{
	for (Value* value : DefinedValues)
	{
		if (value->ID == InID)
		{
			return value->Calculate(DefinedValues);
		}
	}
}

void MathContainer::SetValueName(const Value_ID &InID, const std::string &InName)
{
	for (Value* value : DefinedValues)
	{
		if (value->ID == InID)
		{
			value->ID.name = InName;
		}
	}
}