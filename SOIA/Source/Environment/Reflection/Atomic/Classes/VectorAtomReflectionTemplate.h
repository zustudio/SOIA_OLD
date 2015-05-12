
#pragma once

#include "VectorAtomReflection.h"

namespace Environment
{
	template<class VectorClass>
	class DLLIMPEXP VectorAtomReflectionTemplate : public VectorAtomReflection
	{
		virtual VoidPointer* StringToObject(const std::string& InString) override
		{
			return nullptr;
		}
		virtual std::string ObjectToString(const VoidPointer& InObject) override
		{
			std::string result;
			VectorClass* p_Object = InObject.CastTo<VectorClass>();

			for (auto p_SubObject : *p_Object)
			{
				result += GetAtomString(VoidPointer(p_SubObject)) + ",";
			}
			return result;
		}
	};
}
