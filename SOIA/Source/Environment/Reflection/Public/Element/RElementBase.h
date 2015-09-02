/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "MemberMirror.h"
#include "RClass.h"
#include "ReflectionMacros.h"

#include <vector>

namespace Environment
{
	//////////////////////////////////////////////////////////////////////////////////////////
	/// \class		RElementBase
	/// \brief		Base class of RElement, supports ReflectionMacros.h via providing ending
	///				implementations of it's typedefs and functions.
	class LIBIMPEXP RElementBase
	{
	public:
		///////////////////////////////////////////////////////////////////////
		// Typedefs
		using Type = RElementBase;
		using BaseType = RElementBase;
		using Super = RElementBase;

	protected:
		///////////////////////////////////////////////////////////////////////
		// Functions
		static void INTERNAL_NAME(GetMemberMirrors)(std::vector<MemberMirror*> & InMemberMirrors);
		virtual RClass* GetClass();
		static RClass* StaticClass();

		///////////////////////////////////////////////////////////////////////
		// Properties
		static std::vector<MemberMirror*> INTERNAL_NAME(MemberMirrors);
	};
}