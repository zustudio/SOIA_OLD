
#pragma once

#include "ObjectMirror.h"

namespace Environment
{
	template<typename Type>
	class ObjectMirrorTemplate : public ObjectMirror
	{
	public:
		constexpr ObjectMirrorTemplate(Type& InObjectToMirror, const std::string& InName)
			: ObjectMirror(InName),
			ObjectToMirror(&InObjectToMirror)
		{}
		virtual VoidPointer Get() override
		{
			VoidPointer pointer = VoidPointer(ObjectToMirror, EMemoryType::Stack);
			return pointer;
		}
		virtual bool SetIfTypesMatch(const VoidPointer& InPointer) override
		{
			auto object = InPointer.CastTo<Type>();
			if (object)
			{
				*ObjectToMirror = *object;
				return true;
			}
			else
			{
				return false;
			}
		}
		Type* ObjectToMirror;
	};
}
