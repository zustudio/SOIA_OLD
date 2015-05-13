
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/SaveFile.h"
using namespace Environment;

#include "Environment/File/Public/FileObject.h"

SaveFile::SaveFile(const std::string &InName, bool bWriteFile)
	: 
	File(InName, bWriteFile),
	TagFactory(),
	LoadedRElements(Range<int>(0,10000))
{}

void SaveFile::PreWrite()
{

}

void SaveFile::PostRead()
{
	// save all loaded relements into new container
	std::vector<RElement*> RElements;
	for (VoidPointer p_Object : Content)
	{
		RElement** p_Element = p_Object.CastTo<RElement*>();
		if (p_Element)
		{
			RElements.push_back(*p_Element);
		}
	}
	LoadedRElements = RContainer(Range<int>(0, 100000), RElements);

	//resolve pointers of relements with container
	int n = Content.size();
	for (int i = 0; i < n; i++)
	{
		FileObject fileObject = FileObjects[i];
		VoidPointer* updatedElement = fileObject.ResolvePointers(&LoadedRElements);
		if (updatedElement)
			Content[i] = *updatedElement;
	}
}

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
		while (!InStream->eof() && InStream->peek() != ',')
		{
			tags.push_back(TagFactory.FromStream(*InStream));
		}
		InStream->get();
		FileObject object = ObjectFactory.FromTags(tags);
		result = object.CreateObject();
		FileObjects.push_back(object);
		return result;
	}
	return nullptr;
}
