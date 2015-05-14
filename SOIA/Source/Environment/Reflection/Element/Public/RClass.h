
#pragma once

#include "Environment/Reflection/Type/Public/TypeID.h"
#include <string>

namespace Environment
{
	class RElement;
	class DLLIMPEXP RClass
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


	private:
		////////////////////////////////////////////////////////////////
		// Variables
		TypeID Type;
		TypeID BaseType;
	};
}
