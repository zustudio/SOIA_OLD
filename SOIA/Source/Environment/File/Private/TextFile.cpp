
#include "Definitions.h"

#include "TextFile.h"
using namespace Environment;

TextFile::TextFile(const std::string &InName, bool bWriteFile)
	: File_DEPRECATED(InName, bWriteFile)
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
	std::string* text = new std::string();
	std::getline(*InStream, *text);
	return new VoidPointer(text);
}

void TextFile::PreWrite()
{

}

void TextFile::PostRead()
{

}