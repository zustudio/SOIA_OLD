
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(BackupTool, RTool)
	class LIBIMPEXP BackupTool : public BackupTool_Base
	{
		RCLASS_BEGIN();

		BackupTool(const RPointer<RDialogue>& InDialogue = nullptr);

		RFUNCTION(cmd_save)
		bool cmd_save(RElement* const & InElementName, const std::string& InFileName);

		RFUNCTION(cmd_load)
			bool cmd_load(RElement* const & InElementName, const std::string& InFileName);

		RCLASS_END();
	};
}