
#include "Definitions.h"

#include "Path.h"
using namespace Environment;

#include <algorithm>
#include <regex>


Path::Path(const std::string & InName)
	:
	Name("")
{
	std::regex regex("(\\\\)");
	auto match = std::smatch();
	Name = std::regex_replace(InName, regex, "/");
}

Path Path::AppendFolder(const std::string & InName) const
{
	return Path(Name + InName + "/");
}

Path Path::AppendFile(const std::string & InName) const
{
	return Path(Name + InName);
}

Path Path::StripDotName() const
{
	std::string newName = Name;

	std::regex regex = std::regex("([^/]*\\.[^/]*)");
	auto match = std::smatch();
	bool result = std::regex_search(Name, match, regex);
	if (result)
	{
		int pos = match.position();
		int len = match.length();
		std::string smatch = match[1];
		if (match.position() + match.length() == Name.size())
		{
			newName = Name.substr(0, match.position());
		}
	}

	return Path(newName);
}

std::string Path::GetName() const
{
	std::regex regex = std::regex(".*/([^/]+)/?");
	auto match = std::smatch();
	bool result = std::regex_match(Name, match, regex);
	if (result)
	{
		return match[1];
	}
	else
		return "";
}

const std::string& Path::ToString() const
{
	return Name;
}

