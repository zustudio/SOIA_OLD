
#pragma once

#include "RClass.h"

#include <vector>

namespace Environment
{
	class RElement;

	class LIBIMPEXP ElementReflectionProvider
	{
	public:
		ElementReflectionProvider();
		~ElementReflectionProvider();

		void Register(RClass* InClass);

		RClass* GetClass(const TypeID& InType);

	private:
		std::vector<RClass*> Classes;

	};
}