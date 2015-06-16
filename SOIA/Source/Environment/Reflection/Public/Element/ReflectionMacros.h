
#pragma once

#include "RClass.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RCLASS

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
	virtual Environment::RClass* GetClass() override {return GetClassByType(Environment::TypeID::FromType<ClassType##_Base>());} \
	static Environment::RClass* StaticClass() {return GetClassByType(Environment::TypeID::FromType<ClassType##_Base>());}

#define RBASECLASS(ClassType,SuperClassType,ConstOperations) \
	RBASECLASS_DEFINITION( \
		ClassType, \
		SuperClassType, \
		RBASECLASS_CONSTRUCTOR(ClassType,SuperClassType,ConstOperations) \
		RBASECLASS_BODY(ClassType,SuperClassType))

#define RCLASS(ClassType,SuperClassType) RBASECLASS(ClassType,SuperClassType,RegisterClass<ClassType>();)

#define RABSTRACTCLASS(ClassType,SuperClassType) RBASECLASS(ClassType,SuperClassType,RegisterAbstractClass<ClassType>();)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// RATTRIBUTE & RFUNCTION

#define REFLECT_FUNC_NAME _Internal_ReflectObject

#define RCLASS_BEGIN() \
private: \
template<int n> \
void REFLECT_FUNC_NAME() \
{}; \
template<> \
void REFLECT_FUNC_NAME<__COUNTER__>() \
{ static constexpr const int myCount = __COUNTER__; } \
public: 

#define RATTRIBUTE_BASE(object,name) \
private: \
template<> \
void REFLECT_FUNC_NAME<__COUNTER__>() \
{ \
	static constexpr const int myCount = __COUNTER__; \
	AttributeMirrors.push_back(new ObjectMirrorTemplate<decltype(object)>(object, name )); \
	GetAtomReflectionProvider()->Reflect<decltype(object)>(); \
	REFLECT_FUNC_NAME<myCount - 3>(); \
}; \
public: 

#define RPROPERTY(object) RATTRIBUTE_BASE(object,#object)

#define RFUNCTION(object) \
private: \
Environment::FunctionInterface* object##_Generated = CreateFunction<Type>(this, &Type::object); \
RATTRIBUTE_BASE(object##_Generated,#object) \
public:

#define RCLASS_END() \
private: \
void ReflectAttributes() \
{ \
	REFLECT_FUNC_NAME<__COUNTER__ - 2>(); \
} \
public:


