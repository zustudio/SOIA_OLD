
#pragma once

#include "RElement.h"

namespace Environment
{

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
		template<typename... CtorArgTypes> explicit ClassType##_Base(CtorArgTypes... CtorArgs) : SuperClassType(CtorArgs...) {} \
		virtual Environment::RClass* GetClass() override {return GetClassByType(Environment::TypeID::FromType<ClassType##_Base<TemplateType>>());} \
		static Environment::RClass* StaticClass() {return GetClassByType(Environment::TypeID::FromType<ClassType##_Base<TemplateType>>());} \
	};
	RTEMPLATECLASS(RWrapper,WrappedClass,RElement)
	
	template<typename WrappedClass>
	class RWrapper : public RWrapperTemplate_Base<WrappedClass>
	{
		RCLASS_BEGIN()
			RWrapper()
			: BaseType(),
			WrappedObject(new WrappedClass())
			{}

		WrappedClass* WrappedObject;

		RCLASS_END()
	};
		/*class RWrapper : public RClassWrapper_Base
	{
		RCLASS_BEGIN()
			RWrapper();

		RCLASS_END()
	};*/
}