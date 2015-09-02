/// Intelligence Project - SOIA
/// \file
/// \copyright
/// \brief		Provides macros for reflecting classes and their attributes (properties and functions)

#pragma once

#include "RClass.h"
#include "RFunctionTemplate.h"
#include "MemberMirrorTemplate.h"

#include <type_traits>

#define INTERNAL_NAME(name) _Internal_##name

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RCLASS

#define RTEMPLATECLASS(ClassType,TemplateType,SuperClassType) \
/** \name Internally generated*/ \
/** \{*/ \
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
			GlobalRClassProvider()->Register<ClassType<TemplateType>>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType<TemplateType>>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			GlobalRClassProvider()->Register<ClassType<TemplateType>>(); \
			return GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType<TemplateType>>()); \
		} \
	}; \
/** \}*/

#define RABSTRACTCLASS(ClassType,SuperClassType) \
/** \name Internally generated*/ \
/** \{*/ \
	class ClassType; \
	class ClassType##_Base : public SuperClassType \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType; \
		using BaseType = ClassType##_Base; \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{ \
			GlobalRClassProvider()->RegisterAbstract<ClassType>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			GlobalRClassProvider()->RegisterAbstract<ClassType>(); \
			return GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
	}; \
/** \}*/

#define RCLASS(ClassType,SuperClassType) \
/** \name Internally generated*/ \
/** \{*/ \
	class ClassType; \
	class ClassType##_Base : public SuperClassType \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType; \
		using BaseType = ClassType##_Base; \
		static std::vector<Environment::MemberMirror*> INTERNAL_NAME(MemberMirrors); \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{ \
			GlobalRClassProvider()->RegisterConcrete<ClassType>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			GlobalRClassProvider()->RegisterConcrete<ClassType>(); \
			return GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
	}; \
	std::vector<Environment::MemberMirror*> __declspec(selectany) ClassType##_Base::INTERNAL_NAME(MemberMirrors); \
/** \}*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RPROPERTY & RFUNCTION



#define REFLECT_FUNC_NAME INTERNAL_NAME(ReflectObject)

#define RCLASS_BEGIN() \
/** \name Internally generated*/ \
/** \{*/ \
	public: \
		virtual Environment::VoidPointer GetVoidPointer() /**< Super great function */\
		{ \
			return Environment::VoidPointer(this, EMemoryType::NotOwned); \
		} \
	protected: \
		static void INTERNAL_NAME(GetMemberMirrors)(std::vector<Environment::MemberMirror*> & InMemberMirrors) \
		{ \
			InMemberMirrors.insert(InMemberMirrors.end(), INTERNAL_NAME(MemberMirrors).begin(), INTERNAL_NAME(MemberMirrors).end()); \
			Super::INTERNAL_NAME(GetMemberMirrors)(InMemberMirrors); \
		} \
		virtual std::vector<Environment::MemberMirror*> GetMemberMirrors() \
		{ \
			std::vector<Environment::MemberMirror*> memberMirrors; \
			INTERNAL_NAME(GetMemberMirrors)(memberMirrors); \
			return memberMirrors; \
		} \
		template<int n> \
		typename std::enable_if<n==__COUNTER__>::type REFLECT_FUNC_NAME() \
		{ static constexpr const int myCount = __COUNTER__; } \
/** \}*/ \
	public:

#define RATTRIBUTE_BASE(object,name) \
	template<int n> \
	typename std::enable_if<n==__COUNTER__>::type REFLECT_FUNC_NAME() \
	{ \
		static constexpr const int myCount = __COUNTER__; \
		INTERNAL_NAME(MemberMirrors).push_back(new Environment::MemberMirrorTemplate<Type,decltype(object)>(&Type::object, name )); \
		Environment::GlobalAtomConverterProvider()->Reflect<decltype(object)>(); \
		REFLECT_FUNC_NAME<myCount - 3>(); \
	}

#define RPROPERTY(object) \
	RATTRIBUTE_BASE(object,#object)

#define RFUNCTION(object) \
	Environment::RFunction* object##_Generated = Environment::CreateFunction<Type>(this, &Type::object, #object); \
	RATTRIBUTE_BASE(object##_Generated,#object)

#define RCLASS_END() \
/**\name Internally generated*/ \
/**\{*/\
	private: \
		void ReflectAttributes() \
		{ \
			if (INTERNAL_NAME(MemberMirrors).size() == 0) \
			REFLECT_FUNC_NAME<__COUNTER__ - 2>(); \
		} \
	public: \
/**\}*/
