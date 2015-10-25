/// Intelligence Project - SOIA
/// \brief		Provides macros for reflecting classes and their attributes (properties and functions)

#pragma once

#include "RClass.h"
#include "RFunctionTemplate.h"
#include "MemberMirrorTemplate.h"
#include "GlobalReflectionProviders.h"

#include <type_traits>

#define INTERNAL_NAME(name) _Internal_##name
#define ATTRIBUTE_WEAK __attribute__((weak))
// for windows: __declspec(selectany)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RCLASS

#define RTEMPLATECLASS(ClassType,TemplateType,SuperClassType) \
/** \name Internally generated*/ \
/** \{*/ \
	class ClassType##_CommonBase : public SuperClassType \
	{ \
	public: \
		template<typename... CtorArgTypes> explicit ClassType##_CommonBase(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{} \
		static std::vector<Environment::MemberMirror*> INTERNAL_NAME(MemberMirrors); \
	}; \
	std::vector<Environment::MemberMirror*> ATTRIBUTE_WEAK ClassType##_CommonBase::INTERNAL_NAME(MemberMirrors); \
	\
	template<typename TemplateType> \
	class ClassType; \
	template<typename TemplateType> \
	class ClassType##_Base : public ClassType##_CommonBase \
	{ \
		public: \
		using Super = SuperClassType; \
		using Type = ClassType<TemplateType>; \
		using CommonBaseType = ClassType##_CommonBase; \
		using BaseType = ClassType##_Base<TemplateType>; \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : CommonBaseType(CtorArgs...) \
		{ \
		Environment::GlobalRClassProvider()->Register<ClassType<TemplateType>>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return Environment::GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType<TemplateType>>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
		Environment::GlobalRClassProvider()->Register<ClassType<TemplateType>>(); \
			return Environment::GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType<TemplateType>>()); \
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
		static std::vector<Environment::MemberMirror*> INTERNAL_NAME(MemberMirrors); \
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) \
		{ \
		Environment::GlobalRClassProvider()->RegisterAbstract<ClassType>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return Environment::GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
		Environment::GlobalRClassProvider()->RegisterAbstract<ClassType>(); \
			return Environment::GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
	}; \
	std::vector<Environment::MemberMirror*> ATTRIBUTE_WEAK ClassType##_Base::INTERNAL_NAME(MemberMirrors); \
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
			Environment::GlobalRClassProvider()->RegisterConcrete<ClassType>(); \
		} \
		virtual Environment::RClass* GetClass() override \
		{ \
			return Environment::GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
		static Environment::RClass* StaticClass() \
		{ \
			Environment::GlobalRClassProvider()->RegisterConcrete<ClassType>(); \
			return Environment::GlobalRClassProvider()->GetClass(Environment::TypeID::FromType<ClassType>()); \
		} \
	}; \
	std::vector<Environment::MemberMirror*> ATTRIBUTE_WEAK ClassType##_Base::INTERNAL_NAME(MemberMirrors); \
/** \}*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RPROPERTY & RFUNCTION



#define REFLECT_FUNC_NAME INTERNAL_NAME(ReflectObject)

#define RTEMPLATECLASS_BEGIN(ClassType,TemplateType) \
public: \
	using Super = typename ClassType##_Base<TemplateType>::Super; \
	using Type = typename ClassType##_Base<TemplateType>::Type; \
	using CommonBaseType = typename ClassType##_Base<TemplateType>::CommonBaseType; \
	using BaseType = typename ClassType##_Base<TemplateType>::BaseType; \
	RCLASS_BEGIN();

#define RCLASS_BEGIN() \
/** \name Internally generated*/ \
/** \{*/ \
	public: \
		virtual Environment::VoidPointer GetVoidPointer() \
		{ \
			return Environment::VoidPointer(this, Environment::EMemoryType::NotOwned); \
		} \
	protected: \
		static void INTERNAL_NAME(GetMemberMirrors)(std::vector<Environment::MemberMirror*> & InMemberMirrors) \
		{ \
			InMemberMirrors.insert(InMemberMirrors.end(), BaseType::INTERNAL_NAME(MemberMirrors).begin(), BaseType::INTERNAL_NAME(MemberMirrors).end()); \
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
		BaseType::INTERNAL_NAME(MemberMirrors).push_back(new Environment::MemberMirrorTemplate<Type,decltype(object)>(&Type::object, name )); \
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
			if (BaseType::INTERNAL_NAME(MemberMirrors).size() == 0) \
			REFLECT_FUNC_NAME<__COUNTER__ - 2>(); \
		} \
	public: \
/**\}*/

#define RTEMPLATECLASS_END() \
	RCLASS_END()
