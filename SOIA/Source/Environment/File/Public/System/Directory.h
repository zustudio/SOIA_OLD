
#pragma once

#include "Atom.h"

#include "Path.h"

#include <string>
#include <vector>

namespace Environment
{
	enum class EDirectoryVisibility : int
	{
		All,
		NotSystem
	};
	class LIBIMPEXP Directory : public Atom
	{
	public:
		Directory(const Path& InPath);

		bool Create();
		std::vector<Directory> GetSubDirectories(EDirectoryVisibility InDirVisibility = EDirectoryVisibility::NotSystem) const;

		template<class FileClass>
		std::vector<FileClass> GetFiles() const
		{
			std::vector<Path> outPaths;
			std::vector<FileClass> result;
			GetFileSystem()->GetAccess()->GetFilePaths(PathToDir, outPaths);

			for (auto path : outPaths)
			{
				result.push_back(FileClass(path));
			}
			return result;
		}

		Path const& GetPath() const;

		static Directory FromString(const std::string& InString);
		static std::string ToString(const Directory& InObject);

	private:
		Path PathToDir;
	};
}