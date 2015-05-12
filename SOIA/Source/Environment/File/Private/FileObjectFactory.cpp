
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/FileObjectFactory.h"
using namespace Environment;

#include "Environment/Reflection/Element/Public/RElement.h"

FileObject FileObjectFactory::FromTags(const std::vector<PropertyTag>& InTags)
{
	RClass* ContentClass = nullptr;
	std::vector<VoidPointer> attributes;

	if (InTags.size())
	{
		// 1st: try to find type of first tag in global element reflection provider
		ContentClass =GetElementReflectionProvider()->GetClass(InTags[0].TypeString);
		if (ContentClass)
		{
			// if tags indeed belong to element, than load other tags into attributes
			for (auto iter = InTags.begin() + 1; iter < InTags.end(); iter++)
			{
				attributes.push_back(*(*iter).Object);
			}
		}
		else
		{
			// if no element class was found, than load first Tag into Object
			if (InTags.size())
				attributes.push_back(*InTags[0].Object);
		}
	}

	return FileObject(ContentClass, attributes);
}
FileObject FileObjectFactory::FromObject(RElement* InObject)
{
	return FileObject(InObject->GetClass(), InObject->CreateReflection().Attributes);
}