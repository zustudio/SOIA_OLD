
#pragma once

#include "Value.h"

namespace Environment
{
	enum class EVariableMode
	{
		FunctionParameter,
		Constant
	};

	class LIBIMPEXP Variable : public Value
	{
	public:
		Variable();

		void MakeConstant(double InConstantValue);
		void MakeFunctionParameter(int InParameterNumber);
		
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
		virtual void PrepareCache() override {}

		EVariableMode Mode;
		int ParameterNumber;
		double ConstantValue;

	};
}