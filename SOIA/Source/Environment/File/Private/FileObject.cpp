
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/FileObject.h"
using namespace Environment;

#include "Environment/Reflection/Element/Public/RPointer.h"

FileObject::FileObject(RClass* InClass, const std::vector<VoidPointer>& InAttributes)
{
	Class = InClass;
	Attributes = InAttributes;
	Object = nullptr;
	bIsReflected = false;
}

VoidPointer* FileObject::CreateObject()
{
	if (Class)
	{
		ElementReflection reflection = ElementReflection(Attributes);
		RElement* result = Class->GetDefaultObject();
		Object = nullptr;
		if (result->LoadReflection(reflection, true))
		{
			bIsReflected = true;
			Object = new VoidPointer(*new RElement*(result));
		}
		return Object;
	}
	else
	{
		Object = nullptr;
		if (Attributes.size())
			Object = new VoidPointer(Attributes[0]);
		return Object;
	}
}

VoidPointer* FileObject::ResolvePointers(RContainer* InContainer)
{
	if (!bIsReflected)
	{
		return nullptr;
	}

	int n = Attributes.size();
	for (int i = 0; i < n; i++)
	{
		VoidPointer p_Attribute = Attributes[i];
		RPointer* p_PointerAttribute = p_Attribute.CastTo<RPointer>();
		if (p_PointerAttribute)
		{
			p_PointerAttribute->Container = InContainer;
			Attributes[i] = p_PointerAttribute->ToVoidPointer();
		}
		std::vector<RPointer>* p_v_PointerAttributes = p_Attribute.CastTo<std::vector<RPointer> >();
		std::vector<RElement*>* v_p_Elements = new std::vector<RElement*>();
		if (p_v_PointerAttributes)
		{
			for (auto pointerAttribute : *p_v_PointerAttributes)
			{
				pointerAttribute.Container = InContainer;
				v_p_Elements->push_back(pointerAttribute.Resolve());
			}
			Attributes[i] = VoidPointer(*v_p_Elements);
		}
	}
	(*Object->CastTo<RElement*>())->LoadReflection(ElementReflection(Attributes), true);
	return Object;
}