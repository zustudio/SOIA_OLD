
#pragma once

#include "ICom.h"
#include <string>

namespace SO
{
	namespace Com
	{
		class Com_Handle
		{
		public:
			Com_Handle(ICom* NewPointer, const std::string &NewName);
			~Com_Handle();

			ICom* Pointer;
			std::string Name;
		};
	}
}