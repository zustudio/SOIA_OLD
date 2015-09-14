/// Intelligence Project - SOIA

#pragma once

#include "RWrapperInterface.h"

namespace Environment
{
	/// \class		RWrapper
	/// \brief		Wraps not reflected classes so that they can be accessed via the element hierarchy.
	/// \details	Wrapper automatically creates an object of it's template type. This object is created 
	///				on the first Get() call, because it's type may not be known in the constructor in case 
	///				this class is constructed via it's RClass.
	RTEMPLATECLASS(RWrapper,WrappedClass,RWrapperInterface)
	template<typename WrappedClass>
	class LIBIMPEXP RWrapper : public RWrapper_Base<WrappedClass>
	{
		RTEMPLATECLASS_BEGIN(RWrapper,WrappedClass)

		RWrapper()
			: BaseType()
		{
			this->OriginalWrapperType = TypeID::FromType<Type>();
		}

		RWrapper(RWrapperInterface* InWrapper)
			: BaseType()
		{
			this->OriginalWrapperType = InWrapper->OriginalWrapperType;
			this->WrappedObject = InWrapper->WrappedObject;
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
			if (!this->WrappedObject)
			{
				Create();
			}
			return this->WrappedObject;
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
			if (this->OriginalWrapperType == TypeID::FromType<Type>())
			{
				this->WrappedObject = CreateInternal<WrappedClass>();
			}
			else
			{
				auto originalWrapper = GlobalRClassProvider()->GetClass(this->OriginalWrapperType)->GetDefaultObject();
				auto castOriginalWrapper = dynamic_cast<RWrapperInterface*>(originalWrapper);
				this->WrappedObject = castOriginalWrapper->Get();
				delete originalWrapper;
			}
		}

		RTEMPLATECLASS_END()
	};
}