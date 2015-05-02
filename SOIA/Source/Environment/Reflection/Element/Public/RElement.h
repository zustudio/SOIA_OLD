
#pragma once

#include "Element_ID.h"
#include "ElementReflection.h"
#include "RClassTemplate.h"
#include "Environment/Reflection/TypeAttribute/Public/ObjectMirror.h"
#include "ElementReflectionProvider.h"

DLLIMPEXP extern Environment::ElementReflectionProvider GlobalReflectionProvider;


#define RCLASS(ClassType,SuperClassType) \
class ClassType; \
class ClassType##_Base: public SuperClassType \
{ \
	public: \
	using Super = SuperClassType; \
	using Type = ClassType; \
	virtual RClass* GetClass() override {return GetClassByType(typeid(ClassType).name());} \
};

namespace Environment
{
	class DLLIMPEXP RElement
	{
		using Super = RElement;
		using Type = RElement;
	public:
		RElement() {};
		virtual ~RElement() {};

		virtual void SetID(Element_ID InID);
		Element_ID& GetID();

		ElementReflection CreateReflection();
		bool LoadReflection(const ElementReflection& InReflection);

		virtual RClass* GetClass();
	protected:
		RClass* GetClassByType(const std::string& InTypeID);

	protected:
		template<typename RType, typename... ReflectedObjectTypes>
		void Reflect(ReflectedObjectTypes&... ReflectedAttributes)
		{
			// reflect my attributes
			rec_Reflect(ReflectedAttributes...);

			// reflect my class
			if (!GlobalReflectionProvider.GetClass(typeid(RType).name()))
			{
				GlobalReflectionProvider.Register(new RClassTemplate<RType>(typeid(RType).name(), typeid(RType::Super).name()));
			}
		}
		template<typename ReflectedObjectType, typename... ReflectedObjectTypes>
		void rec_Reflect(ReflectedObjectType& InReflectedObject, ReflectedObjectTypes&... TailReflectedObjects)
		{
			AttributeMirrors.push_back(new ObjectMirror<ReflectedObjectType>(InReflectedObject));
		}

	private:
		Element_ID ID;
		std::vector<ObjectMirrorInterface*> AttributeMirrors;
	};
}
