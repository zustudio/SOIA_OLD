/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "RElement.h"

namespace Environment
{
	/// \class RWrapperInterface
	/// \brief This interface enables casting of wrapped classes via RWrapper objects
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