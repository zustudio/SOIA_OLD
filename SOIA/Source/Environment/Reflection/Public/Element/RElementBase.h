
#pragma once

#include "MemberMirror.h"
#include "RClass.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP RElementBase
	{
	public:
		using Type = RElementBase;
		using BaseType = RElementBase;
		using Super = RElementBase;

	protected:
		static void Internal_GetMemberMirrors(std::vector<MemberMirror*> & InMemberMirrors);

		//------------------------------
		//--- Class
		virtual RClass* GetClass();
		static RClass* StaticClass();


		static std::vector<MemberMirror*> Internal_MemberMirrors;
	};
}