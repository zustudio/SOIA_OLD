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



//
//#define RCLASS(ClassType,SuperClassType) \
//class ClassType; \
//class ClassType##_Base: public SuperClassType \
//{ \
//	public: \
//	using Super = SuperClassType; \
//	using Type = ClassType; \
//	using BaseType = ClassType##_Base; \
//	\
//	virtual RClass* GetClass() override {return GetClassByType(typeid(BaseType).name());} \
//};

#define RCLASSDEF(ClassType,SuperClassType) \
RCLASS(ClassType,SuperClassType) \
class LIBIMPEXP ClassType : public ClassType##_Base

namespace Environment
{
	class RContainer;
	class LIBIMPEXP RElement
	{
		friend RContainer;
	private:
		using Super = RElement;
		using BaseType = RElement;
	public:
		using IsRElementType = std::true_type;		// sfinae definition
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
		static RClass* GetClassByType(const std::string& InTypeID);

	protected:
		template<typename RType>
		void RegisterClass()
		{
			if (!GetElementReflectionProvider()->GetClass(TypeID::FromType<typename RType::BaseType>()))
			{
				GetElementReflectionProvider()->Register(new RClassTemplate<RType>(TypeID::FromType<typename RType::BaseType>(), TypeID::FromType<typename RType::Super::BaseType>()));
			}
		}
		template<typename RType>
		void RegisterAbstractClass()
		{
			if (!GetElementReflectionProvider()->GetClass(TypeID::FromType<typename RType::BaseType>()))
			{
				GetElementReflectionProvider()->Register(new RAbstractClass(TypeID::FromType<typename RType::BaseType>(), TypeID::FromType<typename RType::Super::BaseType>()));
			}
		}

		template<typename... ReflectedObjectTypes>
		void Reflect(ReflectedObjectTypes&... ReflectedAttributes)
		{
			// reflect my attributes
			rec_Reflect(ReflectedAttributes...);
		}
		template<typename ReflectedObjectType, typename... ReflectedObjectTypes>
		void rec_Reflect(ReflectedObjectType& InReflectedObject, ReflectedObjectTypes&... TailReflectedObjects)
		{
			GetAtomReflectionProvider()->Reflect<ReflectedObjectType>();
			AttributeMirrors.push_back(new ObjectMirrorTemplate<ReflectedObjectType>(InReflectedObject, ""));
			rec_Reflect(TailReflectedObjects...);
		}
		void rec_Reflect()	{}

	protected:
		RContainer* Container;
		Element_ID ID;
		std::vector<ObjectMirror*> AttributeMirrors;
	};
}
