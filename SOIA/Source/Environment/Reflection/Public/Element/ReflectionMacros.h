
#pragma once

#include "RClass.h"
#include "RFunctionTemplate.h"
#include <type_traits>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RCLASS

#define RTEMPLATECLASS(ClassType,TemplateType,SuperClassType) \
	template<typename TemplateType> \
	class ClassType; \
	template<typename TemplateType> \
	class ClassType##_Base : public SuperClassType \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType<TemplateType>; \
		using BaseType = ClassType##_Base<TemplateType>; \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{ \
			GetElementReflectionProvider()->Register<ClassType<TemplateType>>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return GetElementReflectionProvider()->GetClass(Environment::TypeID::FromType<ClassType<TemplateType>>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			GetElementReflectionProvider()->Register<ClassType<TemplateType>>(); \
			return GetElementReflectionProvider()->GetClass(Environment::TypeID::FromType<ClassType<TemplateType>>()); \
		} \
	};

#define RABSTRACTCLASS(ClassType,SuperClassType) \
	class ClassType; \
	class ClassType##_Base : public SuperClassType \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType; \
		using BaseType = ClassType##_Base; \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{ \
			GetElementReflectionProvider()->RegisterAbstract<ClassType>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return GetElementReflectionProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			GetElementReflectionProvider()->RegisterAbstract<ClassType>(); \
			return GetElementReflectionProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
	};

#define RCLASS(ClassType,SuperClassType) \
	class ClassType; \
	class ClassType##_Base : public SuperClassType \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType; \
		using BaseType = ClassType##_Base; \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{ \
			GetElementReflectionProvider()->RegisterConcrete<ClassType>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return GetElementReflectionProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			GetElementReflectionProvider()->RegisterConcrete<ClassType>(); \
			return GetElementReflectionProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
	};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RPROPERTY & RFUNCTION

#define REFLECT_FUNC_NAME _Internal_ReflectObject

#define RCLASS_BEGIN() \
private: \
template<int n> \
typename std::enable_if<n==__COUNTER__,void>::type REFLECT_FUNC_NAME() \
{ static constexpr const int myCount = __COUNTER__; } \
public: 

#define RATTRIBUTE_BASE(object,name) \
private: \
template<int n> \
typename std::enable_if<n==__COUNTER__,void>::type REFLECT_FUNC_NAME() \
{ \
	static constexpr const int myCount = __COUNTER__; \
	AttributeMirrors.push_back(new Environment::ObjectMirrorTemplate<decltype(object)>(object, name )); \
	Environment::GetAtomReflectionProvider()->Reflect<decltype(object)>(); \
	REFLECT_FUNC_NAME<myCount - 3>(); \
}; \
public: 

#define RPROPERTY(object) RATTRIBUTE_BASE(object,#object)

#define RFUNCTION(object) \
private: \
Environment::RFunction* object##_Generated = Environment::CreateFunction<Type>(this, &Type::object, #object); \
RATTRIBUTE_BASE(object##_Generated,#object) \
public:

#define RCLASS_END() \
private: \
void ReflectAttributes() \
{ \
	REFLECT_FUNC_NAME<__COUNTER__ - 2>(); \
} \
public:


