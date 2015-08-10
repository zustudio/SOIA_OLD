
#pragma once

#include "Value.h"

namespace Environment
{
	class LIBIMPEXP Variable : public Value
	{
	public:
		Variable(int InVariableNumber, double InContent);

		virtual void SetID(ElementID InID) override;
		virtual double Calculate(const std::vector<Value*> &InDefinedValues) override;

		int VariableNumber;
		double Content;
	};
}