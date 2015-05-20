
#pragma once

#include "Environment/Reflection/Atomic/Public/Atom.h"

#include "Environment/Reflection/Type/Public/VoidPointer.h"
#include <string>

namespace Environment
{
	class DLLIMPEXP Element_ID : public Atom
	{
	public:
		//////////////////////////////////////////////////////////////////
		// Init
		Element_ID();
		static std::string ToString(const Element_ID& InID);
		static Element_ID FromString(const std::string& InString);

		//////////////////////////////////////////////////////////////////
		// Access
		bool operator == (const Element_ID &other) const;

		//////////////////////////////////////////////////////////////////
		// Properties
		int UniqueIdentifier;
		std::string Name;
	};
}