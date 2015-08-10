
#pragma once

#include "RContainer.h"

#include "Operation.h"
#include "Value.h"
#include "FunctionCache.h"

namespace Environment
{
	class LIBIMPEXP MathContainer : public RContainer
	{
	public:
		MathContainer();

		/*ElementID& DefineValue(Value*);
		ElementID RedefineValue(const ElementID&, Value*);*/
		double CalculateValue(const ElementID &InID);
		double CalculateValue(const std::string& InName);
		void SetValueName(const ElementID &InID, const std::string &InName);

		/*double CalculateFunction(const ElementID &InID);*/

		//ElementID FreeID;
		//std::vector<Value*> DefinedValues;
		FunctionCache* FuncCache;
	};
}