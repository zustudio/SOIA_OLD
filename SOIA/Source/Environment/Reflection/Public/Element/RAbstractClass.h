/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "RClass.h"

namespace Environment
{
	/// RClass implementation that does not provide a default object.
	class LIBIMPEXP RAbstractClass : public RClass
	{
	public:
		RAbstractClass(const TypeID& InTypeID, const TypeID& InSuperTypeID);
		virtual RElement* GetDefaultObject() override;
		virtual bool IsAbstract() override;
	};
}