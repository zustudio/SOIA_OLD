
#pragma once

#include "AtomReflection.h"

#include "RPointer.h"

namespace Environment
{
	template<typename RType>
	class PointerReflectionTemplate : public AtomReflection
	{
		virtual bool IsType(const std::string& InTypeID) override
		{
			/*std::regex pattern("class (\\w+)::(\\w+) \\*");
			auto result = std::smatch();
			bool success = std::regex_match(InTypeID, result, pattern);
			return success;*/
			return (TypeID(InTypeID) == TypeID::FromType<RType>());
		}
		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			return GetAtomObject(InString, TypeID::FromType<RPointer>());
		}

		template<typename = typename std::decay<decltype(*std::declval<RType>())>::type::IsRElementType>
		VoidPointer NewPointer(int, RType& InObject)
		{
			return VoidPointer(*new RPointer(InObject, TypeID::FromType<RType>()));
		}

		VoidPointer NewPointer(float, RType& InObject)
		{
			return VoidPointer(*InObject);
		}

		virtual std::string ObjectToString(VoidPointer& InObject) override
		{
			std::string result;
			RType* p_Object = InObject.CastTo<RType>();
			//InObject = VoidPointer(*new RPointer(*p_Object, InObject.GetTypeID()));
			InObject = NewPointer(0, *p_Object);

			result = GetAtomString(InObject);

			return result;
		}
		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) override
		{
			if (GetReflectedClass(InObject.GetTypeID().Dereference()))
			{
				InObject.OverrideType(TypeID::FromType<RElement*>());
				RElement** pp_RElement = InObject.CastTo<RElement*>();
				if (pp_RElement)
				{
					return { *pp_RElement };
				}
			}
			return {};
		}
	};
}
