
#pragma once

#include "Environment/Reflection/ID/Public/RElement.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP Value : public RElement
	{
	public:
		//virtual void SetID(Element_ID InID);

		virtual double Calculate(const std::vector<Value*> &DefinedValues) = 0;

		//Element_ID ID;
	};
}