
#pragma once

#include "RClass.h"

#include <vector>

namespace Environment
{
	class RElement;

	class LIBIMPEXP ElementReflectionProvider
	{
	public:
		void Register(RClass* InClass);

		RClass* GetClass(const TypeID& InType);

	private:
		std::vector<RClass*> Classes;

	};
}