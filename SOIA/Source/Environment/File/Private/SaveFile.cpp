
#include "Definitions.h"

#include "SaveFile.h"
using namespace Environment;

#include "FileObject.h"
#include "LogProvider.h"

SaveFile::SaveFile(const Path &InPath)
	: 
	IOFile(InPath),
	TagFactory()
{}

void SaveFile::AddElement(RElement* const& InElement, ESaveMode InSaveMode)
{
	//TODO: add invidual std::vector<Relement*> container

	RElement** p_InElement = new RElement*(InElement);

	switch (InSaveMode)
	{
	case Environment::ESaveMode::Single:
	{
		Content.push_back(VoidPointer(p_InElement));
	}
	break;
	case Environment::ESaveMode::Recursive:
	{
		std::vector<VoidPointer> newContent;
		newContent.push_back(VoidPointer(p_InElement));
		PreWrite(newContent);
		for (VoidPointer& element : newContent)
		{
			Content.push_back(element);
		}
	}
	break;
	default:
	break;
	}
}

RElement* SaveFile::GetElement(int InNum, const std::vector<RElement*>& InReferenced)
{
	PostRead(FileObjects[InNum], InReferenced);
	RElement* element = Content[InNum].CastAndDereference<RElement*>();
	return element;
}

void SaveFile::Write()
{
	LOGSTATUS("Preparing writing to file...");
	//PreWrite();
	Open(EFileMode::Write);
	LOGSTATUS("Writing to file...");
	for (VoidPointer p_Obj : Content)
	{
		WriteObject(p_Obj);
	}
	Close();
}

void SaveFile::Read()
{
	Open(EFileMode::Read);
	LOGSTATUS("Reading from file...");
	VoidPointer* readObject;
	do
	{
		readObject = ReadObject();
		if (readObject)
		{
			VoidPointer p = *readObject;
			Content.push_back(p);
		}

	} while (readObject);
	Close();
}

void SaveFile::PreWrite(std::vector<VoidPointer>& InContainer)
{
	// add all objects that are pointed to inside object to content
	for (int i = 0; i < InContainer.size(); i++)
	{
		auto p_Object = InContainer[i];
		RElement** pp_Element = p_Object.CastTo<RElement*>();
		if (*pp_Element)
		{
			auto attributes = (*pp_Element)->CreateReflection().Attributes;
			for (auto attribute : attributes)
			{
				std::vector<RElement*> p_AttributeElements = GetAtomReflectionProvider()->GetReflection(attribute.GetTypeID())->ObjectToRElements(attribute);
				for (RElement* p_AttributeElement : p_AttributeElements)
				{
					if (p_AttributeElement && InContainer.end() == Find(InContainer, p_AttributeElement,
						[](const VoidPointer& InVP) -> RElement* {return InVP.CastAndDereference<RElement*>(); }))
					{
						InContainer.push_back(VoidPointer(new RElement*(p_AttributeElement)));
					}
				}
			}
		}
	}
}

void SaveFile::PostRead(FileObject& InFileObject, const std::vector<RElement*>& InReferenced)
{
	// save all referenced elements into new container
	auto LoadedRElements = RContainer(Range<int>(0, 100000), InReferenced);

	InFileObject.ResolvePointers(&LoadedRElements);

	////resolve pointers of relements with container
	//int n = Content.size();
	//for (int i = 0; i < n; i++)
	//{
	//	FileObject fileObject = FileObjects[i];
	//	VoidPointer* updatedElement = fileObject.ResolvePointers(&LoadedRElements);
	//	if (updatedElement)
	//		Content[i] = *updatedElement;
	//}
}


void SaveFile::WriteObject(const VoidPointer& InObject)
{
	RElement** object = InObject.CastTo<RElement*>();
	if (object)
	{
		GetOutStream() << TagFactory.FromObject(ObjectFactory.FromObject(*object)).CompleteString << std::endl;
	}
}

VoidPointer* SaveFile::ReadObject()
{
	VoidPointer* result;
	std::ifstream& inStream = GetInStream();

	while (!inStream.eof())
	{
		std::vector<PropertyTag> tags;
		while (!inStream.eof() && inStream.peek() != ',')
		{
			tags.push_back(TagFactory.FromStream(inStream));
		}
		inStream.get();
		FileObject object = ObjectFactory.FromTags(tags);
		result = object.CreateObject();
		FileObjects.push_back(object);
		return result;
	}
	return nullptr;
}
