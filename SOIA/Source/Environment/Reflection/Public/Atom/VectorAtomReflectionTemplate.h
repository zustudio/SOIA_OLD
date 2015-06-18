
#pragma once

#include "AtomReflection.h"

#include "RPointer.h"

namespace Environment
{
	template<class VectorClass>
	class LIBIMPEXP VectorAtomReflectionTemplate : public AtomReflection
	{
		virtual bool IsType(const std::string& InTypeString)
		{
			return InTypeString == std::string(TypeID::FromType<VectorClass>());
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

			
			std::vector<RPointer>* pointerVector = new std::vector<RPointer>();
			VectorClass* vector = new VectorClass;
			auto itemType = TypeID::FromType<typename VectorClass::value_type>();
			for (auto string : singleStrings)
			{
				VoidPointer* vp_object = GetAtomObject(string, itemType);
				if (itemType.IsPointer())
					pointerVector->push_back(vp_object->CastAndDereference<RPointer>());
				else
					vector->push_back(vp_object->CastAndDereference<typename VectorClass::value_type>());
			}

			if (itemType.IsPointer())
				return new VoidPointer(*pointerVector);
			else
				return new VoidPointer(*vector);
		}
		virtual std::string ObjectToString(VoidPointer& InObject) override
		{
			std::string result;
			VectorClass* p_Object = InObject.CastTo<VectorClass>();

			for (auto p_SubObject : *p_Object)
			{
				VoidPointer vp_p_SubObject = VoidPointer(p_SubObject);
				result += GetAtomString(vp_p_SubObject) + "|";
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
			if (GetReflectedClass(TypeID::FromType<typename VectorClass::value_type>().Dereference()))
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
