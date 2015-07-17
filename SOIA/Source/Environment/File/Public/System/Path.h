
#pragma once

#include <string>

namespace Environment
{
	class LIBIMPEXP Path
	{
	public:
		Path(const std::string& InName);

		Path AppendFolder(const std::string& InName) const;
		Path AppendFile(const std::string& InName) const;

		Path StripDotName() const;

		std::string GetName() const;

		const std::string& ToString() const;

	private:
		std::string Name;
	};
}