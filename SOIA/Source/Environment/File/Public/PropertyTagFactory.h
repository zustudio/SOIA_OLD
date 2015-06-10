
#pragma once

#include "PropertyTag.h"
#include "FileObject.h"
#include "AtomReflectionProvider.h"

namespace Environment
{
	class LIBIMPEXP PropertyTagFactory
	{
	public:
		PropertyTagFactory();

		PropertyTag FromStream(std::istream& InStream);
		PropertyTag FromObject(const FileObject& InObject);
		PropertyTag FromSimpleObject(VoidPointer& InObject);

	private:
		std::string ObjectToString(VoidPointer& InPointer);
		VoidPointer* StringToObject(const std::string& InType, const std::string& InContent);
		std::string StreamToString(std::istream& InStream, const char& InStringStart, const char& InStringEnd);
		std::vector<std::string> StringToList(const std::string& InString, const char& InSeperator);
		inline std::string RemoveStartEndChar(const std::string& InString);

	private:
		PropertyTag* ErrorResult;
	};
}