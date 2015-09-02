/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "Atom.h"

#include "VoidPointer.h"

#include <string>

namespace Environment
{
	//////////////////////////////////////////////////////////////////////////////////////////
	/// \class		ElementID
	/// \brief		Provides an unique ID for RElement objects.
	/// \details	With this ID they can be serialized and retain their identity.
	class LIBIMPEXP ElementID : public Atom
	{
		//////////////////////////////////////////////////////////////////
		// Functions

	public:
		///\name Init
		///\{
			ElementID(int const & InIdentifier = -1);
		///\}

		///\name Access
		///\{
			int const & ToInt() const;
		///\}

		///\name Operators
		///\{
			operator int() const;
			bool operator == (const ElementID &other) const;
		///\}

		///\name Atom implementation
		///\{
			static std::string StaticToString(const ElementID& InID);
			static ElementID StaticToObject(const std::string& InString);
		///\}

		////////////////////////////////////////////////////////////////
		// Variables

	public:
		///\name Properties
		///\{
			int Identifier;
		///\}
	};
}