
#pragma once

#include "Environment/Reflection/ID/Public/RContainer.h"

#include "Operation.h"
#include "Value.h"
#include "FunctionCache.h"

namespace Environment
{
	class DLLIMPEXP MathContainer : public RContainer
	{
	public:
		MathContainer();

		/*Element_ID& DefineValue(Value*);
		Element_ID RedefineValue(const Element_ID&, Value*);*/
		double CalculateValue(const Element_ID &InID);
		void SetValueName(const Element_ID &InID, const std::string &InName);

		/*double CalculateFunction(const Element_ID &InID);*/

		//Element_ID FreeID;
		//std::vector<Value*> DefinedValues;
		FunctionCache FuncCache;
	};
}