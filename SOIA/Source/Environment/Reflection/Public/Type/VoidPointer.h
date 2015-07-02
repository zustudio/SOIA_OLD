
#pragma once

#include "TypeID.h"
#include "PointerCounter.h"
#include "DeleterFunctionTemplate.h"
#include <typeinfo>
#include <string>
#include <assert.h>

namespace Environment
{
	enum class EMemoryType
	{
		Unknown,
		NotOwned,
		Stack,
		Heap
	};

	class LIBIMPEXP VoidPointer
	{
	protected:
		VoidPointer()
			:
			Target(nullptr),
			DeleterFunction(nullptr),
			Counter(nullptr),
			Type(""),
			MemoryType(EMemoryType::Unknown)
		{}
	public:
		//----- init -----
		VoidPointer(const VoidPointer &ObjToCopy)
			:
			Target(ObjToCopy.Target),
			DeleterFunction(ObjToCopy.DeleterFunction),
			Counter(ObjToCopy.Counter),
			Type(ObjToCopy.Type),
			MemoryType(ObjToCopy.MemoryType)
		{
			if (IsValid())
				Counter->Increase();
		}
		VoidPointer& operator=(const VoidPointer& InOther)
		{
			Target = InOther.Target;
			DeleterFunction = InOther.DeleterFunction;
			Counter = InOther.Counter;
			Type = InOther.Type;
			MemoryType = InOther.MemoryType;
			if (IsValid())
			{
				Counter->Increase();
			}
			return *this;
		}
		VoidPointer(VoidPointer&& InOther)
			:
			Target(InOther.Target),
			DeleterFunction(InOther.DeleterFunction),
			Counter(InOther.Counter),
			Type(InOther.Type),
			MemoryType(InOther.MemoryType)
		{
			if (IsValid())
			Counter->Increase();
		}
		VoidPointer& operator=(VoidPointer&& InOther)
		{
			Target = InOther.Target;
			DeleterFunction = InOther.DeleterFunction;
			Counter = InOther.Counter;
			Type = InOther.Type;
			MemoryType = InOther.MemoryType;
			if (IsValid())
			{
				Counter->Increase();
			}
			return *this;
		}
		template<typename T>
		explicit VoidPointer(T* NewObject, EMemoryType InMemoryType = EMemoryType::Heap)
			:
			Target((void*)NewObject),
			DeleterFunction(new DeleterFunctionTemplate<T>()),
			Type(TypeID::FromType<T>()),
			MemoryType(InMemoryType),
			Counter(new PointerCounter())
		{
			if (IsValid())
				Counter->Increase();
		}

		virtual ~VoidPointer()
		{
			if (IsValid())
			{
				if (!Counter->Decrease())
				{
					if (MemoryType == EMemoryType::Heap)
					{
						DeleterFunction->Execute(Target);
					}
					delete DeleterFunction;
					delete Counter;
				}
			}
		}

		static VoidPointer Nullpointer()
		{
			return VoidPointer();
		}

		//----- public cast functionality -----
		template<typename T>
		T* CastTo() const
		{
			if (IsType<T>())
				return (T*)Target;
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
				return (NewType*)Target;
			else
				return nullptr;
		}

		//----- public type checking -----
		const TypeID& GetTypeID() const;
		void OverrideType(const TypeID& InNewTypeID);

		operator bool() const;

		bool IsValid() const;

		bool IsNullPointer();

		//----- operators -----
		bool operator==(const VoidPointer& InOther) const
		{
			return (Target == InOther.Target && Type == InOther.Type);
		}

		//----- type checking -----
		bool IsChildOf(const TypeID& Other) const;
	private:
		template<typename T>
		bool IsType() const
		{
			TypeID ID2 = TypeID::FromType<T>();
			return ID2 == Type;
		}

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		void* Target;
		Function<void, void*>* DeleterFunction;
		PointerCounter* Counter;
		TypeID Type;
		EMemoryType MemoryType;

	};
}

