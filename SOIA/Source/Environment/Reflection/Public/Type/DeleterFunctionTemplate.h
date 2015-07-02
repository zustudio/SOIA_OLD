
#pragma once

#include "Function.h"

namespace Environment
{
	template<class ObjectClass>
	class DeleterFunctionTemplate : public Function<void, void*>
	{
	public:
		virtual void Execute(void* InTarget) override
		{
			ObjectClass* CastTarget = static_cast<ObjectClass*>(InTarget);
			delete CastTarget;
		}
	};
}