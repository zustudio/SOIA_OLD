
#pragma once

#include "RWrapperInterface.h"

namespace Environment
{
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