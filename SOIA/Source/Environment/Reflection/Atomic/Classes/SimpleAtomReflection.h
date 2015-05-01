
#pragma once

#include "Environment/Reflection/Atomic/Public/AtomReflectionInterface.h"

namespace Environment
{
	template<typename SimpleType>
	class SimpleAtomReflection : public AtomReflectionInterface
	{
	public:
		typedef std::string(*ToStringConverter_FunctionType)(const SimpleType&);
		typedef SimpleType(*ToObjectConverter_FunctionType)(const std::string&);
		////////////////////////////////////////////////////////////////
		// initialize reflection with constructor
		SimpleAtomReflection(ToStringConverter_FunctionType InToStringConverter, ToObjectConverter_FunctionType InToObjectConverter)
		{
			ToStringConverter = InToStringConverter;
			ToObjectConverter = InToObjectConverter;
		}

		////////////////////////////////////////////////////////////////
		// reflection functionality
		virtual bool IsType(const std::string& InTypeName) override
		{
			return (InTypeName == typeid(SimpleType).name());
		}
		virtual std::string ObjectToString(const VoidPointer& InObject) override
		{
			SimpleType object = *InObject.CastTo<SimpleType>();
			return (*ToStringConverter)(object);
		}
		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			SimpleType object = (*ToObjectConverter)(InString);
			return new VoidPointer(*new SimpleType(object));
		}

		////////////////////////////////////////////////////////////////
		// converter functions
		ToStringConverter_FunctionType ToStringConverter;
		ToObjectConverter_FunctionType ToObjectConverter;
	};
}