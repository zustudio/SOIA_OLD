
#pragma once

#include "Environment/Reflection/Atomic/Public/AtomReflection.h"

#include "Environment/Reflection/Element/Public/RPointer.h"

namespace Environment
{
	template<typename RType>
	class PointerReflectionTemplate : public AtomReflection
	{
		virtual bool IsType(const std::string& InTypeID) override
		{
			std::regex pattern("class (\\w+)::(\\w+) \\*");
			auto result = std::smatch();
			bool success = std::regex_match(InTypeID, result, pattern);
			return success;
		}
		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			return nullptr;
		}
		virtual std::string ObjectToString(VoidPointer& InObject) override
		{
			std::string result;
			RType* p_Object = InObject.CastTo<RType>();
			InObject = VoidPointer(*new RPointer(*p_Object, InObject.GetTypeID()));

			result = GetAtomString(InObject);

			return result;
		}
	};
}
