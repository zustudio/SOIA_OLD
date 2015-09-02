/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "RClass.h"

#include <string>

namespace Environment
{
	class RElement;
}

namespace Environment
{
	/// RClass implementation that allows the creation of default objects of it's type.
	template<typename RType>
	class RClassTemplate : public RClass
	{
	public:
		RClassTemplate(const TypeID& InTypeID, const TypeID& InBaseTypeID) : RClass(InTypeID, InBaseTypeID)
		{}

		virtual RElement* GetDefaultObject() override
		{
			return new RType();
		}
		virtual bool IsAbstract() override
		{
			return false;
		}
	};
}
