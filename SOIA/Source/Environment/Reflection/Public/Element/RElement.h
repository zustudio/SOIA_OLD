/////////////////////////////////////////////////////////////////////////////////////////////
///	Project:	SOIA
///	Author:		Maxim Urschumzew
/// Year:		2015
///

#pragma once

#include "Element_ID.h"
#include "ElementReflection.h"
#include "ElementReflectionProvider.h"
#include "RClassTemplate.h"
#include "RAbstractClass.h"
#include "ObjectMirrorTemplate.h"
#include "ReflectionProviders.h"
#include "ReflectionMacros.h"


#define RCLASSDEF(ClassType,SuperClassType) \
RCLASS(ClassType,SuperClassType) \
class LIBIMPEXP ClassType : public ClassType##_Base

namespace Environment
{
	class RContainer;
	class LIBIMPEXP RElement
	{
		friend RContainer;

		RCLASS_BEGIN()
		using Super = RElement;
		using Type = RElement;
		using BaseType = RElement;

	public:
		RElement();
		virtual ~RElement();

		virtual void SetID(Element_ID InID);
		Element_ID& GetID();
		RContainer* GetContainer();

		ElementReflection CreateReflection();
		bool LoadReflection(const ElementReflection& InReflection, bool bIsPartial);

		std::vector<std::string> GetAttributeNames();
		VoidPointer GetAttribute(const std::string& InName);

		virtual RClass* GetClass();
		static RClass* StaticClass();

	protected:
		RContainer* Container;

		RPROPERTY(ID)
			Element_ID ID;

		std::vector<ObjectMirror*> AttributeMirrors;

		RCLASS_END()
	};
}
