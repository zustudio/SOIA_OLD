
#pragma once

#include "ObjectMirror.h"

namespace Environment
{
	template<typename Type>
	class ObjectMirrorTemplate : public ObjectMirror
	{
	public:
		ObjectMirrorTemplate(Type& InObjectToMirror)
		{
			ObjectToMirror = &InObjectToMirror;
		}
		virtual VoidPointer Get() override
		{
			VoidPointer pointer = VoidPointer(*ObjectToMirror);
			return pointer;
		}
		virtual bool SetIfTypesMatch(const VoidPointer& InPointer) override
		{
			Type* object = InPointer.CastTo<Type>();
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
