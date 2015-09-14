
#pragma once

#include "AtomConverter.h"

#include "ResolvePointerInfo.h"
#include "VoidPointerToUnresolvedRObject.h"

namespace Environment
{
	template<typename RType>
	class PointerConverter : public AtomConverter
	{
		virtual bool IsType(const std::string& InTypeID) override
		{
			return (TypeID(InTypeID) == TypeID::FromType<RType>());
		}
		virtual TypeID GetType() override
		{
			return TypeID::FromType<RType>();
		}


		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			return ToObject_Internal<RType>(0, InString);
		}

		virtual std::string ObjectToString(const VoidPointer& InObject) override
		{
			std::string result = "";
			RType* p_Object = InObject.CastTo<RType>();
			
			if (p_Object && *p_Object)
			{
				result = ToString_Internal<RType>(0, *p_Object);
			}

			return result;
		}
		
		/////////////////////////////////////////////////////////////////////
		// Internal Helpers

		//----- ToObject -----
		template<typename Type>
		static auto ToObject_Internal(int, const std::string& InString) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, VoidPointer*>::type
		{
			ElementID TargetElementID = ElementID(std::atoi(InString.c_str()));

			ResolveInfoInterface* ResolveInfo = new ResolvePointerInfo(TargetElementID, nullptr);

			auto resolveFunc =
				[](VoidPointerToUnresolvedRObject* InThis) -> void
				{
					ResolvePointerInfo* PointerInfo = dynamic_cast<ResolvePointerInfo*>(InThis->GetResolveInfo());
					InThis->CastAndDereference<Type>() = dynamic_cast<Type>(
						AtomConverterHelper::GetElementByID(PointerInfo->TargetElementID, PointerInfo->TargetElementContainer));
				};

			return new VoidPointerToUnresolvedRObject(new Type(nullptr), resolveFunc, ResolveInfo);
		}

		template<typename Type>
		static auto ToObject_Internal(float, const std::string& InString) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type >::value, VoidPointer*>::type
		{
			typedef typename std::remove_pointer<Type>::type InnerType;
			return new VoidPointer(new Type(&AtomConverterHelper::GetAtomObject(InString, TypeID::FromType<InnerType>())->template CastAndDereference<InnerType>()));
			//return new VoidPointer(VoidPointer::Nullpointer());
		}

		//----- ToString -----
		template<typename Type>
		static auto ToString_Internal(int, Type& InObject) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, std::string>::type
		{
			return std::to_string(InObject->GetID().ToInt());
		}

		template<typename Type>
		static auto ToString_Internal(float, Type& InObject) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type >::value, std::string>::type
		{
			return AtomConverterHelper::GetAtomString(VoidPointer(InObject, EMemoryType::NotOwned));
		}


		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) override
		{
			if (AtomConverterHelper::GetReflectedClass(InObject.GetTypeID().Dereference()))
			{
				InObject.OverrideType(TypeID::FromType<RElement*>());
				RElement** pp_RElement = InObject.CastTo<RElement*>();
				if (pp_RElement)
				{
					return{ *pp_RElement };
				}
			}
			return{};
		}
	};
}
