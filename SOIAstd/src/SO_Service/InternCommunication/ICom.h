
#pragma once

#include "ICom.h"

namespace SO
{
	namespace Com
	{
		class ICom
		{
			/////////////////////////////////
			// about this:
			virtual std::string& getName() = 0;

			////////////////////////////////
			// io
			void out(const ICom &target);
			void in(const ICom &caller);
		};
	}
}