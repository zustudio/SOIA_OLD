
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(RWorkspaceTool, RTool);
	class LIBIMPEXP RWorkspaceTool : public RWorkspaceTool_Base
	{
		RCLASS_BEGIN();

		RWorkspaceTool(const RPointer<RDialogue>& InDialogue = RPointer<RDialogue>(nullptr));

		RFUNCTION(cmd_listtypes)
			bool cmd_listtypes();

		RFUNCTION(cmd_type)
			bool cmd_type(TypeID& OutType, const std::string& InTypeName);

		RFUNCTION(cmd_create)
			bool cmd_create(const TypeID& InType, const std::string& InName, RContainer* const& InContainer);

		RFUNCTION(cmd_gui)
			bool cmd_gui(RTool* const & InTool);

		RCLASS_END();
	};
}