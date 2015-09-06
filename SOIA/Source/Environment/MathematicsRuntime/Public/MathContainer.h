
#pragma once

#include "RContainer.h"

#include "Operation.h"
#include "Value.h"
#include "Constant.h"
#include "FunctionCache.h"
#include "Tokenizer.h"
#include "DynamicMathFunction.h"

namespace Environment
{
	enum class ECacheStatus : int
	{
		Dirty = 0,
		Valid = 1
	};

	class LIBIMPEXP MathContainer : public RContainer
	{
		friend DynamicMathFunction;

		enum TokenRuleIdentifiers
		{
			Number,
			VarName,
			FunctionName,
			Parenthesis,
			MultiplyDivide,
			AddSubstract,
			Assignment,
		};

	public:
		MathContainer();

		DynamicMathFunction* ParseString(std::string InString);

	protected:
		double Calculate(Value* InValue, std::vector<double> const & InArguments);

	private:
		Value* CreateValue(Token* InToken);

		void PrepareCache();

	private:
		Tokenizer MathTokenizer;

		FunctionCache* FuncCache;
		ECacheStatus CacheStatus;

		Constant* NULLConstant;

		/*double CalculateValue(const ElementID &InID);
		double CalculateValue(const std::string& InName);
		void SetValueName(const ElementID &InID, const std::string &InName);*/
	};
}