/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "TypeID.h"
#include <string>

namespace Environment
{
	class RElement;
}

namespace Environment
{
	/// \brief		Abstraction of a reflected c++ class.
	/// \details	This RClass object can be used to create default objects of the named type.
	class LIBIMPEXP RClass
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		
		///\name Init
		///\{
			RClass(const TypeID& InType, const TypeID& InSuperType);
			virtual ~RClass();
		///\}

		///\name Definitions for child classes
		///\{
			virtual RElement* GetDefaultObject() = 0;
			virtual bool IsAbstract() = 0;
		///\}

		///\name Type access
		///\{
			TypeID GetType();
			bool IsType(const TypeID& InType);
			bool IsChildOf(RClass* InType) const;
		///\}

	private:
		////////////////////////////////////////////////////////////////
		// Variables
		TypeID Type;
		TypeID BaseType;
	};
}
