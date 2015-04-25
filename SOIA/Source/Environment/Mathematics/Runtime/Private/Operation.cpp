
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/Operation.h"
using namespace Environment;

Operation::Operation(const std::vector<Element_ID> &InOperands)
{
	Operands = InOperands;
}

bool Operation::FindOperands(const std::vector<Value*> &InDefinedValues, Value* &OutOperand0, Value* &OutOperand1, Value* &OutOperand2)
{
	
	Value* OutOperands[] = { nullptr, nullptr, nullptr };

	int found_Num = 0;

	for (Value* value : InDefinedValues)
	{
		for (int i = 0; i < Operands.size(); i++)
		{
			if (Operands.size() > found_Num && value->GetID() == Operands[i])
			{
				OutOperands[i] = value;
				found_Num++;
			}
		}
	}

	OutOperand0 = OutOperands[0];
	OutOperand1 = OutOperands[1];
	OutOperand2 = OutOperands[2];

	if (found_Num == Operands.size())
		return true;
	else
		return false;
}