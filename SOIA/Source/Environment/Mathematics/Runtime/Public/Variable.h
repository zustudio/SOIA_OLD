
#pragma once

#include "Value.h"

namespace Environment
{
	class DLLIMPEXP Variable : public Value
	{
	public:
		Variable(int InVariableNumber, double InContent);

		virtual void SetID(Element_ID InID) override;
		virtual double Calculate(const std::vector<Value*> &InDefinedValues) override;

		int VariableNumber;
		double Content;
	};
}