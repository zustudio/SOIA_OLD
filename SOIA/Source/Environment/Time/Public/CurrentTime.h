
#pragma once

#include <string>

namespace Environment
{
	class LIBIMPEXP CurrentTime
	{
	public:
		static std::string ToString();
	private:
		static const std::string GetTimeString();
	};
}