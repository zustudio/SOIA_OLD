
#pragma once

#include "Function.h"

namespace Environment
{
	template<class ObjectClass>
	class DestructorFunctionTemplate : public Function
	{
	public:
		DestructorFunctionTemplate(ObjectClass* InObject)
			:
			Object(InObject)
		{}
		virtual void Execute() override
		{
			Object->ObjectClass::~ObjectClass();
		}
		ObjectClass* Object;
	};
}