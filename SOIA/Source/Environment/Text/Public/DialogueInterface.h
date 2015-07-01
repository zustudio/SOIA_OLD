
#pragma once

#include <string>

namespace Environment
{
	class LIBIMPEXP DialogueInterface
	{
	public:
		virtual void Write(const std::string& InText) = 0;
		virtual void WriteLine(const std::string& InText) = 0;
		virtual void GetNextLine(std::string& OutText) = 0;
	};
}