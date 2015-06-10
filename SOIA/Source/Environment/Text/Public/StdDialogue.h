
#pragma once

#include "DialogueInterface.h"

namespace Environment
{
	class LIBIMPEXP StdDialogue : public DialogueInterface
	{
		virtual void WriteLine(const std::string& InText) override;
		virtual void GetNextLine(std::string& OutText) override;
	};
}