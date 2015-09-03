
#pragma once

#include "AtomConverter.h"
#include "AtomConverterHelper.h"

#include "ResolveVectorInfo.h"

namespace Environment
{
	template<class VectorClass>
	class LIBIMPEXP VectorConverter : public AtomConverter
	{
		virtual bool IsType(const std::string& InTypeString)
		{
			return InTypeString == std::string(TypeID::FromType<VectorClass>());
		}
		virtual TypeID GetType() override
		{
			return TypeID::FromType<VectorClass>();
		}

		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			std::vector<std::string> singleStrings;
			auto i_begin = InString.begin();
			for (auto i_current = InString.begin(); i_current != InString.end(); i_current++)
			{
				if (*i_current == '|')
				{
					singleStrings.push_back(std::string(i_begin, i_current));
					i_begin = i_current + 1;
				}
			}

			return ToObject_Internal<VectorClass>(0, singleStrings);
		}

		/////////////////////////////////////////////////////////////////////
		// Internal Helpers

		//----- ToObject -----
		template<typename Type>
		static auto ToObject_Internal(int, const std::vector<std::string>& InStrings) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<typename Type::value_type>::type>::value, VoidPointer*>::type
		{
			auto firstResult = new VectorClass;
			auto Objects = std::vector<VoidPointerToUnresolvedRObject>();
			for (auto string : InStrings)
			{
				auto unresolvedVPointer = dynamic_cast<VoidPointerToUnresolvedRObject*>(AtomConverterHelper::GetAtomObject(string, TypeID::FromType<typename Type::value_type>()));
				firstResult->push_back(unresolvedVPointer->CastAndDereference<typename VectorClass::value_type>());
				Objects.push_back(*unresolvedVPointer);
			}
			ResolveInfoInterface* ResolveInfo = new ResolveVectorInfo(Objects, nullptr);


			auto resolveFunc = [](VoidPointerToUnresolvedRObject* InThis)
			{
				ResolveVectorInfo* VectorInfo = dynamic_cast<ResolveVectorInfo*>(InThis->GetResolveInfo());

				VectorClass& result = InThis->CastAndDereference<VectorClass>();

				int n = VectorInfo->Objects.size();
				for (int i = 0; i < n; i++)
				{
					auto& object = VectorInfo->Objects[i];
					object.Resolve(VectorInfo->TargetElementContainer);
					result[i] = object.CastAndDereference<typename VectorClass::value_type>();
				}
			};

			return new VoidPointerToUnresolvedRObject(firstResult, resolveFunc, ResolveInfo);
		}

		template<typename Type>
		static auto ToObject_Internal(float, const std::vector<std::string>& InStrings) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<typename Type::value_type>::type >::value, VoidPointer*>::type
		{
			VectorClass* vector = new VectorClass;
			auto itemType = TypeID::FromType<typename VectorClass::value_type>();
			for (auto string : InStrings)
			{
				VoidPointer* vp_object = AtomConverterHelper::GetAtomObject(string, itemType);
				vector->push_back(vp_object->CastAndDereference<typename VectorClass::value_type>());
			}

			return new VoidPointer(vector);
		}



		virtual std::string ObjectToString(const VoidPointer& InObject) override
		{
			std::string result;
			VectorClass* p_Object = InObject.CastTo<VectorClass>();

			for (auto p_SubObject : *p_Object)
			{
				VoidPointer vp_p_SubObject = VoidPointer(&p_SubObject, EMemoryType::Stack);
				result += AtomConverterHelper::GetAtomString(vp_p_SubObject) + "|";
			}
			return result;
		}


		template<typename Type>
		auto Push_RElement(int, Type& InObject, std::vector<RElement*>& OutResult) -> typename std::enable_if<std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, void>::type
		{
			OutResult.push_back((RElement*)InObject);
		}

		template<typename Type>
		auto Push_RElement(float, Type& InObject, std::vector<RElement*>& OutResult) -> typename std::enable_if<!std::is_base_of<RElement, typename std::remove_pointer<Type>::type>::value, void>::type
		{}


		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) override
		{
			if (AtomConverterHelper::GetReflectedClass(TypeID::FromType<typename VectorClass::value_type>().Dereference()))
			{
				std::vector<RElement*> result;
				VectorClass* p_Vector = InObject.CastTo<VectorClass>();
				
				for (auto object : *p_Vector)
				{
					Push_RElement<typename VectorClass::value_type>(0, object, result);
				}

				return result;
			}
			return {};

		}
	};
}
