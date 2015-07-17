
#pragma once

#include "RTool.h"

#include "FileSystemProvider.h"

namespace Supervisor
{
	RCLASS(RWorkspaceTool, RTool);
	class LIBIMPEXP RWorkspaceTool : public RWorkspaceTool_Base
	{
		RCLASS_BEGIN();

		RWorkspaceTool(const RPointer<RDialogue>& InDialogue = RPointer<RDialogue>(nullptr));

		RFUNCTION(cmd_typelist)
			bool cmd_typelist();

		RFUNCTION(cmd_type)
			bool cmd_type(TypeID& OutType, const std::string& InTypeName);

		RFUNCTION(cmd_create)
			bool cmd_create(const TypeID& InType, const std::string& InName, RContainer* const& InContainer);

		RFUNCTION(cmd_gui)
			bool cmd_gui(RTool* const & InTool);

		RFUNCTION(cmd_dirlist)
			bool cmd_dirlist();
		
		RFUNCTION(cmd_dir)
			bool cmd_dir(Directory& OutDir, std::string const& InName);

		RFUNCTION(cmd_changedir)
			bool cmd_changedir(const Directory& InDir);

		RFUNCTION(cmd_saveproject)
			bool cmd_saveproject(Directory const& InDir);
		bool SaveRecursive(Directory const& InDir, RElement* const& InElement);
		bool SaveContainer(Directory const& InDir, RContainer* const& InContainer, Directory & OutContainerDir);
		bool SaveElement(Directory const& InDir, RElement* const& InElement);

		RPROPERTY(CurrentDirectory)
			Directory CurrentDirectory;

		RCLASS_END();
	};
}