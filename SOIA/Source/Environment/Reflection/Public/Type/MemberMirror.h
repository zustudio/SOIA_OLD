
#pragma once

#include "VoidPointer.h"
#include "ObjectMirror.h"

namespace Environment
{
	class LIBIMPEXP MemberMirror
	{
	public:
		explicit MemberMirror(const std::string& InName);

		virtual TypeID MemberType() = 0;

		virtual ObjectMirror* ToObjectMirror(VoidPointer const & InOwner) = 0;

		std::string const Name;
	};
}
