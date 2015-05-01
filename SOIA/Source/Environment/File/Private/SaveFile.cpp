
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/SaveFile.h"
using namespace Environment;

SaveFile::SaveFile(const std::string &InName, bool bWriteFile)
	: 
	File(InName, bWriteFile),
	ReflectionProvider(AtomReflectionProvider()),
	TagFactory(&ReflectionProvider)
{}

void SaveFile::WriteObject(const VoidPointer& InObject)
{

}

VoidPointer* SaveFile::ReadObject()
{
	VoidPointer* result;
	auto tag = TagFactory.FromStream(InStream);
	if (tag.TypeString == "ERROR")
		result = nullptr;
	else
	{
		result = tag.Object;
	}
	return result;
}