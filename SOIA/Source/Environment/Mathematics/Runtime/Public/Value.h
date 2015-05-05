
#pragma once

#include "Environment/Reflection/Element/Public/RElement.h"

#include <vector>


namespace Environment
{
	RCLASS(Value,RElement);
	class DLLIMPEXP Value: public Value_Base
	{
	public:
		//virtual void SetID(Element_ID InID);

		

		virtual double Calculate(const std::vector<Value*> &DefinedValues) = 0;

		//Element_ID ID;
	};
}