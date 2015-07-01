
#pragma once

#include "AtomReflection.h"

namespace Environment
{
	template<typename SimpleType>
	class SimpleAtomReflection : public AtomReflection
	{
	public:
		typedef std::string(*ToStringConverter_FunctionType)(const SimpleType&);
		typedef SimpleType(*ToObjectConverter_FunctionType)(const std::string&);
		////////////////////////////////////////////////////////////////
		// initialize reflection with constructor
		SimpleAtomReflection(ToStringConverter_FunctionType InToStringConverter, ToObjectConverter_FunctionType InToObjectConverter)
			: AtomReflection()
		{
			ToStringConverter = InToStringConverter;
			ToObjectConverter = InToObjectConverter;
		}
		virtual ~SimpleAtomReflection()
		{}

		////////////////////////////////////////////////////////////////
		// reflection functionality
		virtual bool IsType(const std::string& InTypeName) override
		{
			return (InTypeName == std::string(TypeID::FromType<SimpleType>()));
		}
		virtual std::string ObjectToString(VoidPointer& InObject) override
		{
			SimpleType object = *InObject.CastTo<SimpleType>();
			return (*ToStringConverter)(object);
		}
		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			SimpleType object = (*ToObjectConverter)(InString);
			return new VoidPointer(new SimpleType(object));
		}

		////////////////////////////////////////////////////////////////
		// converter functions
		ToStringConverter_FunctionType ToStringConverter;
		ToObjectConverter_FunctionType ToObjectConverter;
	};
}
