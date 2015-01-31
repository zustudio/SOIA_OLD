
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
				T* temp/* = new T*/;
				Object = (void*) &NewObject;
				ID = std::string(typeid(temp).name());
			}
			template<typename T>
			T* CastTo() const
			{
				T* temp/* = new T*/;
				std::string ID2 = std::string(typeid(temp).name());

				if (ID2 == ID)
					return (T*)Object;
				else
					return nullptr;
			}

		private:
			void* Object;
			std::string ID;

		};
	}
}