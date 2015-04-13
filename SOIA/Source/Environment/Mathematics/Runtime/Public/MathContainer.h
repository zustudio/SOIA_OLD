
#pragma once

#include "Operation.h"
#include "Value.h"
#include "Value_ID.h"
#include "FunctionCache.h"

namespace Environment
{
	class DLLIMPEXP MathContainer
	{
	public:
		MathContainer();

		Value_ID& DefineValue(Value*);
		Value_ID RedefineValue(const Value_ID&, Value*);
		double CalculateValue(const Value_ID &InID);
		void SetValueName(const Value_ID &InID, const std::string &InName);

		/*double CalculateFunction(const Value_ID &InID);*/

		Value_ID FreeID;
		std::vector<Value*> DefinedValues;
		FunctionCache FuncCache;
	};
}