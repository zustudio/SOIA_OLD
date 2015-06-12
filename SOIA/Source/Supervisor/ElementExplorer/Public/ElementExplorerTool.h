
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(ElementExplorerTool,RTool)
	class LIBIMPEXP ElementExplorerTool : public ElementExplorerTool_Base
	{
		RCLASS_BEGIN();

		ElementExplorerTool(DialogueInterface* InDialogue = nullptr);

		RFUNCTION(cmd_ls);
		bool cmd_ls();

		RFUNCTION(cmd_cc);
		bool cmd_cc(const std::string& InContainerName);

		std::string GetCurrentPath();

		RPROPERTY(CurrentContainer);
		RContainer* CurrentContainer;

		RCLASS_END();
	};
}