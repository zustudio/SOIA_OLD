
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/SaveFile.h"
using namespace Environment;

#include "Environment/File/Public/FileObject.h"

SaveFile::SaveFile(const std::string &InName, bool bWriteFile)
	: 
	File(InName, bWriteFile),
	ReflectionProvider(AtomReflectionProvider()),
	TagFactory(&ReflectionProvider)
{}

void SaveFile::WriteObject(const VoidPointer& InObject)
{
	RElement** object = InObject.CastTo<RElement*>();
	if (object)
	{
		(*OutStream) << TagFactory.FromObject(ObjectFactory.FromObject(*object)).CompleteString << ',' << std::endl;
	}
}

VoidPointer* SaveFile::ReadObject()
{
	VoidPointer* result;

	while (!InStream->eof())
	{
		std::vector<PropertyTag> tags;
		while (InStream->peek() != ',' && !InStream->eof())
		{
			tags.push_back(TagFactory.FromStream(*InStream));
		}
		FileObject object = ObjectFactory.FromTags(tags);
		return object.CreateObject();
	}
	return nullptr;
}
