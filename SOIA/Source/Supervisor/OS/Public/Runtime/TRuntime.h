
#pragma once

#include "TTool.h"

#include "ElementFile.h"
#include "FileSystemProvider.h"
#include "Directory.h"
#include "TMainTool.h"

namespace Supervisor
{
	RCLASS(TRuntime, TTool)
	class LIBIMPEXP TRuntime : public TRuntime_Base
	{
		RCLASS_BEGIN()
			TRuntime();

		RFUNCTION(cmd_start)
			bool cmd_start(RElement* const & InMainTool);

		RFUNCTION(cmd_typelist)
			bool cmd_typelist();

		RFUNCTION(cmd_type)
			bool cmd_type(Environment::TypeID& OutType, const std::string& InTypeName);

		RFUNCTION(cmd_create)
			bool cmd_create(const Environment::TypeID& InType, const std::string& InName, Environment::RContainer* const& InContainer);

		RFUNCTION(cmd_rename)
			bool cmd_rename(Environment::RElement* const& InElement, std::string const& InNewName);

		RFUNCTION(cmd_gui)
			bool cmd_gui(TTool* const & InTool);

		RFUNCTION(cmd_dirlist)
			bool cmd_dirlist();
		
		RFUNCTION(cmd_dir)
			bool cmd_dir(Environment::Directory& OutDir, std::string const& InName);

		RFUNCTION(cmd_changedir)
			bool cmd_changedir(const Environment::Directory& InDir);

		RFUNCTION(cmd_saveproject)
			bool cmd_saveproject(Environment::Directory const& InDir);
		bool SaveRecursive(Environment::Directory const& InDir, Environment::RElement* const& InElement);
		bool SaveContainer(Environment::Directory const& InDir, Environment::RContainer* const& InContainer, Environment::Directory & OutContainerDir);
		bool SaveElement(Environment::Directory const& InDir, Environment::RElement* const& InElement);

		RFUNCTION(cmd_loadproject)
			bool cmd_loadproject(Environment::Directory const& InDir);
		bool LoadRecursive(Environment::Directory const& InDir, std::vector<Environment::RElement*>& OutAllElements);
		bool LoadContainer(Environment::ElementFile& InSaveFile, std::vector<Environment::RElement*> const& InChildren, Environment::RContainer*& OutContainer);
		bool LoadElement(Environment::ElementFile& InSaveFile, Environment::RElement* & OutElement);

		RPROPERTY(CurrentDirectory)
			Environment::Directory CurrentDirectory;

		RCLASS_END()
	};
}
