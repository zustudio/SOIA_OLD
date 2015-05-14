
#pragma once

#include "Element_ID.h"
#include "ElementReflection.h"
#include "ElementReflectionProvider.h"
#include "RClassTemplate.h"
#include "RAbstractClass.h"
#include "Environment/Reflection/Type/Public/ObjectMirrorTemplate.h"
#include "Environment/Global/Public/GlobalsImport.h"


#define RBASECLASS_DEFINITION(ClassType,SuperClassType,CONTENT) \
	class ClassType; \
	class ClassType##_Base: public SuperClassType \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType; \
		using BaseType = ClassType##_Base; \
		CONTENT \
	};

#define RBASECLASS_CONSTRUCTOR(ClassType,SuperClassType,ConstructorOperations) \
	template<typename... CtorArgTypes> ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) {ConstructorOperations}

#define RBASECLASS_BODY(ClassType,SuperClassType) \
	virtual RClass* GetClass() override {return GetClassByType(typeid(ClassType##_Base).name());}

#define RBASECLASS(ClassType,SuperClassType,ConstOperations) \
	RBASECLASS_DEFINITION( \
		ClassType, \
		SuperClassType, \
		RBASECLASS_CONSTRUCTOR(ClassType,SuperClassType,ConstOperations) \
		RBASECLASS_BODY(ClassType,SuperClassType))

#define RCLASS(ClassType,SuperClassType) RBASECLASS(ClassType,SuperClassType,RegisterClass<ClassType>();)

#define RABSTRACTCLASS(ClassType,SuperClassType) RBASECLASS(ClassType,SuperClassType,RegisterAbstractClass<ClassType>();)

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
class DLLIMPEXP ClassType : public ClassType##_Base

namespace Environment
{
	class DLLIMPEXP RElement
	{
		using Super = RElement;
		using BaseType = RElement;
	public:
		RElement();
		virtual ~RElement() {};

		virtual void SetID(Element_ID InID);
		Element_ID& GetID();

		ElementReflection CreateReflection();
		bool LoadReflection(const ElementReflection& InReflection, bool bIsPartial);

		virtual RClass* GetClass();
	protected:
		RClass* GetClassByType(const std::string& InTypeID);

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
			AttributeMirrors.push_back(new ObjectMirrorTemplate<ReflectedObjectType>(InReflectedObject));
			rec_Reflect(TailReflectedObjects...);
		}
		void rec_Reflect()	{}

	private:
		Element_ID ID;
		std::vector<ObjectMirror*> AttributeMirrors;
	};
}
