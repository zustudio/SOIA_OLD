
#pragma once

#include "TypeID.h"
#include <typeinfo>
#include <string>
#include <assert.h>

namespace Environment
{
	class LIBIMPEXP VoidPointer
	{
	protected:
		VoidPointer(void* InObject, TypeID InID)
			:
			Object(InObject),
			ID(InID)
		{}
	public:
		//----- init -----
		VoidPointer(const VoidPointer &ObjToCopy, bool NOP = false) : 
			Object(ObjToCopy.Object),
			ID(ObjToCopy.ID)
		{}
		template<typename T>
		explicit VoidPointer(const T &NewObject) :
			Object((void*)&NewObject),
			ID(TypeID::FromType<T>())
		{}
		virtual ~VoidPointer()
		{}

		static VoidPointer Nullpointer()
		{
			return VoidPointer(nullptr, TypeID::FromType<std::nullptr_t>());
		}

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
			if (IsType<NewType>() || IsChildOf(TypeID::FromType<NewType>()))
				return (NewType*)Object;
			else
				return nullptr;
		}

		//----- public type checking -----
		const TypeID& GetTypeID() const;
		void OverrideType(const TypeID& InNewTypeID);

		bool IsNullPointer();

		//----- operators -----
		bool operator==(const VoidPointer& InOther) const
		{
			return (Object == InOther.Object && ID == InOther.ID);
		}

		//----- type checking -----
		bool IsChildOf(const TypeID& Other) const;
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

