
#pragma once

#include "TypeID.h"
#include <string>

namespace Environment
{
	class RElement;
	class LIBIMPEXP RClass
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----

		RClass(const TypeID& InType, const TypeID& InSuperType);
		virtual ~RClass();

		//----- Definitions for child classes -----

		virtual RElement* GetDefaultObject() = 0;
		virtual bool IsAbstract() = 0;

		//----- Type Access -----

		TypeID GetType();
		bool IsType(const TypeID& InType);
		bool IsChildOf(RClass* InType) const;


	private:
		////////////////////////////////////////////////////////////////
		// Variables
		TypeID Type;
		TypeID BaseType;
	};
}
