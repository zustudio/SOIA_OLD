
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(BackupTool, RTool)
	class LIBIMPEXP BackupTool : public BackupTool_Base
	{
		RCLASS_BEGIN();

		BackupTool(Environment::DialogueInterface* InDialogue = nullptr);

		RFUNCTION(cmd_save)
		bool cmd_save(const std::string& InElementName, const std::string& InFileName);

		RCLASS_END();
	};
}