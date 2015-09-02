
#pragma once

#include "AtomConverter.h"

namespace Environment
{
	template<typename SimpleType>
	class SimpleConverter : public AtomConverter
	{
	public:
		typedef std::string(*ToStringConverter_FunctionType)(const SimpleType&);
		typedef SimpleType(*ToObjectConverter_FunctionType)(const std::string&);
		////////////////////////////////////////////////////////////////
		// initialize reflection with constructor
		SimpleConverter(ToStringConverter_FunctionType InToStringConverter, ToObjectConverter_FunctionType InToObjectConverter)
			: AtomConverter()
		{
			ToStringConverter = InToStringConverter;
			ToObjectConverter = InToObjectConverter;
		}
		virtual ~SimpleConverter()
		{}

		////////////////////////////////////////////////////////////////
		// reflection functionality
		virtual bool IsType(const std::string& InTypeName) override
		{
			return (InTypeName == std::string(TypeID::FromType<SimpleType>()));
		}
		virtual TypeID GetType() override
		{
			return TypeID::FromType<SimpleType>();
		}
		virtual std::string ObjectToString(const VoidPointer& InObject) override
		{
			SimpleType object = *InObject.CastTo<SimpleType>();
			return (*ToStringConverter)(object);
		}
		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			SimpleType object = (*ToObjectConverter)(InString);
			return new VoidPointer(new SimpleType(object));
		}
		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) override
		{
			return {};
		}

		////////////////////////////////////////////////////////////////
		// converter functions
		ToStringConverter_FunctionType ToStringConverter;
		ToObjectConverter_FunctionType ToObjectConverter;
	};
}
