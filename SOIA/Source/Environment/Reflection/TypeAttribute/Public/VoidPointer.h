
#pragma once

#include <typeinfo>
#include <string>

namespace Environment
{
	class DLLIMPEXP VoidPointer
	{
	public:
		//----- init -----
		VoidPointer(const VoidPointer &ObjToCopy, bool NOP = false)
		{
			Object = ObjToCopy.Object;
			ID = ObjToCopy.ID;
		}
		template<typename T>
		VoidPointer(const T &NewObject)
		{
			Object = (void*) &NewObject;
			ID = std::string(typeid(T).name());
		}

		//----- public cast functionality -----
		template<typename T>
		T* CastTo() const
		{
			std::string ID2 = std::string(typeid(T).name());

			if (ID2 == ID)
				return (T*)Object;
			else
				return nullptr;
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

		const std::string& GetTypeID() const
		{
			return ID;
		}

		void OverrideType(const std::string& InNewTypeID)
		{
			ID = InNewTypeID;
		}

		//----- type checking -----
	private:
		template<typename T>
		bool IsType() const
		{
			std::string ID2 = std::string(typeid(T).name());
			return ID2 == ID;
		}

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		void* Object;
		std::string ID;

	};
}

