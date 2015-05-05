
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/TextFile.h"
using namespace Environment;

TextFile::TextFile(const std::string &InName, bool bWriteFile)
	: File(InName, bWriteFile)
{}

void TextFile::WriteObject(const VoidPointer& InObject)
{
	std::string* text = InObject.CastTo<std::string>();
	if (text)
	{
		(*OutStream) << text->c_str() << std::endl;
	}
}

VoidPointer* TextFile::ReadObject()
{
	std::string text;
	std::getline(*InStream, text);
	return new VoidPointer(text);
}
