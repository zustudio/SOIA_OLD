
#pragma once

#include "Value.h"

#include "Variable.h"
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

		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
		virtual void PrepareCache() override;

		std::string GenerateParameterName(int InParameterNum);

	/*private:
		void SplitParameterName(std::string const & InName, std::string & OutName, int & OutNumber);*/

	private:
		RPointer<Value> FunctionBody;
		std::vector<RPointer<Variable>> Parameter;

	};
}