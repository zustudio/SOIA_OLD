
#pragma once

#include "VectorAtomReflection.h"

namespace Environment
{
	template<class VectorClass>
	class DLLIMPEXP VectorAtomReflectionTemplate : public VectorAtomReflection
	{
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
			auto itemType = TypeID::FromType<VectorClass::value_type>();
			for (auto string : singleStrings)
			{
				VoidPointer* vp_object = GetAtomObject(string, itemType);
				if (itemType.IsPointer())
					pointerVector->push_back(vp_object->CastAndDereference<RPointer>());
				else
					vector->push_back(vp_object->CastAndDereference<VectorClass::value_type>());
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
				result += GetAtomString(VoidPointer(p_SubObject)) + "|";
			}
			return result;
		}
		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) override
		{
			if (GetElementReflectionProvider()->GetClass(TypeID::FromType<VectorClass::value_type>().Dereference()))
			{
				std::vector<RElement*> result;
				VectorClass* p_Vector = InObject.CastTo<VectorClass>();
				
				for (auto object : *p_Vector)
				{
					result.push_back((RElement*)object);
				}

				return result;
			}
			return {};

		}
	};
}
