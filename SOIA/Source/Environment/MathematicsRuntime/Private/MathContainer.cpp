
#include "Definitions.h"

#include "MathContainer.h"
using namespace Environment;

#include "Constant.h"
#include "Variable.h"

MathContainer::MathContainer() : RContainer(Range<int>(1000,10000000))
{
	FuncCache = new FunctionCache();
	Register(new Constant(0.1), "MathRuntimeVersion");
	Register(new Variable(0, 0));
	Register(FuncCache);
}

//Element_ID& MathContainer::DefineValue(Value* InValue)
//{
//	InValue->SetID(FreeID);
//	FreeID.UniqueIdentifier++;
//
//	DefinedValues.push_back(InValue);
//
//	return InValue->ID;
//}
//Element_ID MathContainer::RedefineValue(const Element_ID& InChangingID, Value* InNewValue)
//{
//	int n = DefinedValues.size();
//	for (int i = 0; i < n; i++)
//	{
//		if (DefinedValues[i]->ID == InChangingID)
//		{
//			InNewValue->SetID(InChangingID);
//			DefinedValues[i] = InNewValue;
//			break;
//		}
//	}
//	Element_ID res = InChangingID;
//	return res;
//}

double MathContainer::CalculateValue(const Element_ID &InID)
{
	Value* element = GetElement<Value>(InID);
	if (element)
	{
		return element->Calculate(GetAllElements<Value>());
	}
	return 35505;
}
double MathContainer::CalculateValue(const std::string& InName)
{
	Value* element = GetElement<Value>(InName);
	if (element)
	{
		return element->Calculate(GetAllElements<Value>());
	}
	return 35505;
}

void MathContainer::SetValueName(const Element_ID &InID, const std::string &InName)
{
	RElement* element = GetElement<Value>(InID);
	element->GetID().Name = InName;
}