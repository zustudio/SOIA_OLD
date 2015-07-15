
#pragma once

#include "Atom.h"

#include "Path.h"

#include <string>
#include <vector>

namespace Environment
{
	class LIBIMPEXP Directory : public Atom
	{
	public:
		Directory(const Path& InPath);

		std::vector<Directory> GetSubDirectories();

		Path const& GetPath() const;

		static Directory FromString(const std::string& InString)
		{
			return Directory(Path(InString));
		}
		static std::string ToString(const Directory& InObject)
		{
			return InObject.GetPath().ToString();
		}

	private:
		Path PathToDir;
	};
}