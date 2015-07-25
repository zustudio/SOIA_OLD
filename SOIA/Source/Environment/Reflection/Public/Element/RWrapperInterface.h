
#pragma once

#include "RElement.h"

namespace Environment
{
	RABSTRACTCLASS(RWrapperInterface,RElement)
	class RWrapperInterface : public RWrapperInterface_Base
	{
		RCLASS_BEGIN()
		RWrapperInterface() 
			: BaseType(),
			WrappedObject(nullptr),
			OriginalWrapperType("")
		{}

		virtual void* Get() = 0;

		void* WrappedObject;

		RPROPERTY(OriginalWrapperType)
			TypeID OriginalWrapperType;

		RCLASS_END()
	};
}