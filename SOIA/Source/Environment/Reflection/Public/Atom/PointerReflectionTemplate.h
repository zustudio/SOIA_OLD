
#pragma once

#include "AtomReflection.h"

#include "ResolvePointerInfo.h"
#include "VoidPointerToUnresolvedRObject.h"

namespace Environment
{
	template<typename RType>
	class PointerReflectionTemplate : public AtomReflection
	{
		virtual bool IsType(const std::string& InTypeID) override
		{
			return (TypeID(InTypeID) == TypeID::FromType<RType>());
		}


		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			return ToObject_Internal<RType>(0, InString);
		}

		virtual std::string ObjectToString(const VoidPointer& InObject) override
		{
			std::string result;
			RType* p_Object = InObject.CastTo<RType>();
			
			result = ToString_Internal<RType>(0, *p_Object);

			return result;
		}
		
		/////////////////////////////////////////////////////////////////////
		// Internal Helpers

		//----- ToObject -----
		template<typename Type>
		static auto ToObject_Internal(int, const std::string& InString) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, VoidPointer*>::type
		{
			Element_ID TargetElementID;
			TargetElementID.UniqueIdentifier = std::atoi(InString.c_str());

			ResolveInfoInterface* ResolveInfo = new ResolvePointerInfo(TargetElementID, nullptr);

			auto resolveFunc =
				[](VoidPointerToUnresolvedRObject* InThis) -> void
				{
					ResolvePointerInfo* PointerInfo = dynamic_cast<ResolvePointerInfo*>(InThis->GetResolveInfo());
					InThis->CastAndDereference<Type>() = dynamic_cast<Type>(
						GetElementByID(PointerInfo->TargetElementID, PointerInfo->TargetElementContainer));
				};

			return new VoidPointerToUnresolvedRObject(new Type(nullptr), resolveFunc, ResolveInfo);
		}

		template<typename Type>
		static auto ToObject_Internal(float, const std::string& InString) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type >::value, VoidPointer*>::type
		{/*
			using InnerType = typename std::remove_pointer<Type>::type;
			return new VoidPointer(new Type(&GetAtomObject(InString, TypeID::FromType<InnerType>())->CastAndDereference<InnerType>()));*/
			return new VoidPointer(VoidPointer::Nullpointer());
		}

		//----- ToString -----
		template<typename Type>
		static auto ToString_Internal(int, Type& InObject) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, std::string>::type
		{
			return std::to_string(InObject->GetID().UniqueIdentifier);
		}

		template<typename Type>
		static auto ToString_Internal(float, Type& InObject) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type >::value, std::string>::type
		{
			return GetAtomString(VoidPointer(InObject, EMemoryType::NotOwned));
		}

		/*template<typename Type>
		static auto Dereference(int, Type& InObject) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, VoidPointer>::type
		{
			return VoidPointer(new RPointer(InObject, TypeID::FromType<Type>()));
		}

		template<typename Type>
		static auto Dereference(float, Type& InObject) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type >::value, VoidPointer>::type
		{
			return VoidPointer(*InObject);
		}*/

		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) override
		{
			if (GetReflectedClass(InObject.GetTypeID().Dereference()))
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
