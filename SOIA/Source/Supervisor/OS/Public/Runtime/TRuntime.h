
#pragma once

#include "TTool.h"

#include "SaveFile.h"
#include "FileSystemProvider.h"

namespace Supervisor
{
	RCLASS(TRuntime, TTool)
	class LIBIMPEXP TRuntime : public TRuntime_Base
	{
		RCLASS_BEGIN()
			TRuntime(const RPointer<RDialogue>& InDialogue = RPointer<RDialogue>(nullptr));

		RFUNCTION(cmd_typelist)
			bool cmd_typelist();

		RFUNCTION(cmd_type)
			bool cmd_type(TypeID& OutType, const std::string& InTypeName);

		RFUNCTION(cmd_create)
			bool cmd_create(const TypeID& InType, const std::string& InName, RContainer* const& InContainer);

		RFUNCTION(cmd_gui)
			bool cmd_gui(TTool* const & InTool);

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

		RFUNCTION(cmd_loadproject)
			bool cmd_loadproject(Directory const& InDir);
		bool LoadRecursive(Directory const& InDir, std::vector<RElement*>& OutAllElements);
		bool LoadContainer(SaveFile& InSaveFile, std::vector<RElement*> const& InChildren, RContainer*& OutContainer);
		bool LoadElement(SaveFile& InSaveFile, RElement* & OutElement);

		RPROPERTY(CurrentDirectory)
			Directory CurrentDirectory;

		RCLASS_END()
	};
}