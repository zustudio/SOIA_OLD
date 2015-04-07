
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

		private:
			void* Object;
			std::string ID;

		};
	}
}
