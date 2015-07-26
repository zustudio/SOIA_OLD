
#pragma once

#include "RWrapperInterface.h"

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
		virtual Environment::RClass* GetClass() override {return GetClassByType(Environment::TypeID::FromType<ClassType<TemplateType>>());} \
		static Environment::RClass* StaticClass() {return GetClassByType(Environment::TypeID::FromType<ClassType<TemplateType>>());} \
	};
	RTEMPLATECLASS(RWrapper,WrappedClass,RWrapperInterface)
	
	template<typename WrappedClass>
	class LIBIMPEXP RWrapper : public RWrapper_Base<WrappedClass>
	{
		RCLASS_BEGIN()

		RWrapper()
			: BaseType()
		{
			OriginalWrapperType = TypeID::FromType<Type>();
		}

		RWrapper(RWrapperInterface* InWrapper)
			: BaseType()
		{
			OriginalWrapperType = InWrapper->OriginalWrapperType;
			WrappedObject = InWrapper->WrappedObject;
		}

		decltype(auto) operator*()
		{
			return ExposeMemberAccessOperator((WrappedClass*)Get());
		}
		decltype(auto) operator->()
		{
			return ExposeMemberAccessOperator((WrappedClass*)Get());
		}

		virtual void* Get() override
		{
			if (!WrappedObject)
			{
				Create();
			}
			return WrappedObject;
		}

		template<typename RType>
		auto CreateInternal() -> typename std::enable_if<std::is_abstract<RType>::value, WrappedClass*>::type
		{
			return nullptr;
		}

		template<typename RType>
		auto CreateInternal() -> typename std::enable_if<!std::is_abstract<RType>::value, WrappedClass*>::type
		{
			return new WrappedClass();
		}

		void Create()
		{
			if (OriginalWrapperType == TypeID::FromType<Type>())
			{
				WrappedObject = CreateInternal<WrappedClass>();
			}
			else
			{
				auto originalWrapper = GetElementReflectionProvider()->GetClass(OriginalWrapperType)->GetDefaultObject();
				auto castOriginalWrapper = dynamic_cast<RWrapperInterface*>(originalWrapper);
				WrappedObject = castOriginalWrapper->Get();
				delete originalWrapper;
			}
		}

		RCLASS_END()
	};
}