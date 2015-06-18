
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

		virtual std::string ObjectToString(VoidPointer& InObject) override
		{
			std::string result;
			RType* p_Object = InObject.CastTo<RType>();
			//InObject = VoidPointer(*new RPointer(*p_Object, InObject.GetTypeID()));
			
			
			result = GetAtomString(Dereference<RType>(0, *p_Object));

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

		//template<typename = typename std::decay<decltype(*std::declval<RType>())>::type::IsRElementType>
		template<typename Type>
		static auto Dereference(int, Type& InObject) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, VoidPointer>::type
		{
			return VoidPointer(*new RPointer(InObject, TypeID::FromType<Type>()));
		}

		template<typename Type>
		static auto Dereference(float, Type& InObject) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type >::value, VoidPointer>::type
		{
			return VoidPointer(*InObject);
		}
	};
}
