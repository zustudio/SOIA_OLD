
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

		bool Create();
		std::vector<Directory> GetSubDirectories();

		Path const& GetPath() const;

		static Directory FromString(const std::string& InString);
		static std::string ToString(const Directory& InObject);

	private:
		Path PathToDir;
	};
}