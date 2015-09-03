
#pragma once

#include "Value.h"

#include "Variable.h"
#include "FunctionCache.h"
#include "RPointer.h"

#include <vector>


namespace Environment
{
	RCLASS(MR_Function, Value)
	class LIBIMPEXP MR_Function : public MR_Function_Base
	{
	public:
		MR_Function(RPointer<Value> InFunctionBody = nullptr, std::vector<RPointer<Variable>> const & InParameter = {});
		void SetBody(RPointer<Value> InFunctionBody);
		void SetSpecialValue(std::vector<double> InOperands, double InResult);
		bool GetCachedFunctionCall(std::vector<double> InOperands, double &OutResult);
		void CacheFunctionCall(std::vector<double> InOperands, double InResult);

		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
		virtual void PrepareCache() override;

		std::string GenerateParameterName(int InParameterNum);


	private:
		RPointer<Value> FunctionBody;
		std::vector<RPointer<Variable>> Parameter;
		FunctionCache Cache;
		FunctionCache SpecialValues;
	};
}