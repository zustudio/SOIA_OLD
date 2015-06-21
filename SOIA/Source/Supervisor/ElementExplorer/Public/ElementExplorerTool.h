
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(ElementExplorerTool,RTool)
	class LIBIMPEXP ElementExplorerTool : public ElementExplorerTool_Base
	{
		RCLASS_BEGIN();

		ElementExplorerTool(const RPointer<RDialogue>& InDialogue = nullptr);

		RFUNCTION(cmd_ls);
		bool cmd_ls();

		RFUNCTION(cmd_pwd)
			bool cmd_pwd(Environment::RContainer*&);

		RFUNCTION(cmd_elem)
			bool cmd_elem(RElement*& OutElement, const std::string& InName);

		RFUNCTION(cmd_cc);
		bool cmd_cc(const std::string& InContainerName);

		RFUNCTION(cmd_attr)
			bool cmd_attr(RElement* const & InElement, std::string const & InAttributeName);

		std::string GetCurrentPath();

		Environment::RContainer* CurrentContainer;

		RCLASS_END();
	};
}
