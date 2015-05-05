
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/FileObject.h"
using namespace Environment;

FileObject::FileObject(RClass* InClass, const std::vector<VoidPointer>& InAttributes)
{
	Class = InClass;
	Attributes = InAttributes;
}

VoidPointer* FileObject::CreateObject()
{
	if (Class)
	{
		ElementReflection reflection = ElementReflection(Attributes);
		RElement* result = Class->GetDefaultObject();
		result->LoadReflection(reflection);
		return new VoidPointer(*new RElement*(result));
	}
	else
	{
		if (Attributes.size())
			return new VoidPointer(Attributes[0]);
		else
			return nullptr;
	}
}
