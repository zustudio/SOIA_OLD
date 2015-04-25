
#pragma once

#include <typeinfo>
#include <string>

namespace SO
{
	namespace Base
	{
		class VoidPointer
		{
		public:
			VoidPointer(const VoidPointer &ObjToCopy)
			{
				Object = ObjToCopy.Object;
				ID = ObjToCopy.ID;
			}
			template<typename T>
			VoidPointer(const T &NewObject)
			{
				Object = (void*) &NewObject;
				ID = std::string(typeid(T*).name());
			}
			template<typename T>
			T* CastTo() const
			{
				std::string ID2 = std::string(typeid(T*).name());

				if (ID2 == ID)
					return (T*)Object;
				else
					return nullptr;
			}
			template<typename T>
			bool IsType() const
			{
				std::string ID2 = std::string(typeid(T).name());

				return (ID2 == ID);
			}
			template<typename T>
			T& GetReference() const
			{
				if (IsType<T>())
				{
					T* p_Object = (T*)Object;
					T& object = *p_Object;
					return object;
				}
				T object = T();
				return object;
			}

		private:
			void* Object;
			std::string ID;

		};
	}
}
