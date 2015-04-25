
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/MathContainer.h"
using namespace Environment;

MathContainer::MathContainer() : RContainer(Range<int>(1000,10000000))
{
	FuncCache = FunctionCache();
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
		
}

void MathContainer::SetValueName(const Element_ID &InID, const std::string &InName)
{
	RElement* element = GetElement<Value>(InID);
	element->GetID().Name = InName;
}