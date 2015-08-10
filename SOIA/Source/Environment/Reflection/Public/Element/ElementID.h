
#pragma once

#include "Atom.h"

#include "VoidPointer.h"
#include <string>

namespace Environment
{
	class LIBIMPEXP ElementID : public Atom
	{
		//////////////////////////////////////////////////////////////////
		// Functions
	public:

		//------------------------------
		//--- Init
		ElementID(int const & InIdentifier);
		static ElementID DefaultObject();

		//------------------------------
		//--- Access
		int const & ToInt() const;

		//------------------------------
		//--- Atom implementation
		static std::string ToString(const ElementID& InID);
		static ElementID FromString(const std::string& InString);

		//------------------------------
		//--- Operators
		operator int() const;
		bool operator == (const ElementID &other) const;

		////////////////////////////////////////////////////////////////
		// Variables
	public:

		//------------------------------
		//--- Properties
		int Identifier;
	};
}