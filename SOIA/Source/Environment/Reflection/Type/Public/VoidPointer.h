
#pragma once

#include "TypeID.h"
#include <typeinfo>
#include <string>
#include <assert.h>

namespace Environment
{
	class DLLIMPEXP VoidPointer
	{
	public:
		//----- init -----
		VoidPointer(const VoidPointer &ObjToCopy, bool NOP = false) : 
			Object(ObjToCopy.Object),
			ID(ObjToCopy.ID)
		{}
		template<typename T>
		VoidPointer(const T &NewObject) :
			Object((void*)&NewObject),
			ID(TypeID::FromType<T>())
		{}

		//----- public cast functionality -----
		template<typename T>
		T* CastTo() const
		{
			if (IsType<T>())
				return (T*)Object;
			else
				return nullptr;
		}
		template<typename T>
		T& CastAndDereference() const
		{
			T* pointer = CastTo<T>();
			assert(pointer);
			return *pointer;
		}
		template<typename NewType>
		NewType* ConvertTo() const
		{
			if (IsType<NewType>())
				return (NewType*)Object;
			else
			{
				if (IsType<std::string>() && typeid(NewType) == typeid(int))
				{
					return (NewType*) new int(std::atoi(((std::string*)Object)->c_str()));
				}
				return nullptr;
			}

		}

		//----- public type checking -----
		const TypeID& GetTypeID() const;
		void OverrideType(const TypeID& InNewTypeID);

		bool IsNullPointer();

		//----- type checking -----
	private:
		template<typename T>
		bool IsType() const
		{
			TypeID ID2 = TypeID::FromType<T>();
			return ID2 == ID;
		}

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		void* Object;
		TypeID ID;

	};
}

