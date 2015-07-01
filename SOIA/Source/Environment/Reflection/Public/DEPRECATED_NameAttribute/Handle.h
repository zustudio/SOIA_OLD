
#pragma once

#include <string>
#include <vector>
#include <deque>

namespace SO
{
	namespace Base
	{
		template<typename T>
		class Handle
		{
		public:
			//////////////////////////////////////////////////////////
			// init
			Handle(T* NewPointer = nullptr, const std::string &NewName = std::string(""), int NewNum = 0)
			{
				Obj = NewPointer;
				MainName = std::string(NewName);
				Num = NewNum;
			}
			~Handle()
			{

			}
			//////////////////////////////////////////////////////////
			// access
			T* getObj(const std::vector<Handle<T> > &Set) const
			{
				if (Obj)
				{
					return Obj;
				}
				else if (Set.size() > 0)
				{
					for (Handle<T> hndl : Set)
					{
						if (hndl.getName() == this->getName() && hndl.Obj)
						{
							return hndl.Obj;
						}
					}
				}
				return nullptr;
			}
			T* getObj() const
			{
				if (Obj)
				{
					return Obj;
				}
				else
				{
					return nullptr;
				}
			}
			/////////////////////////////////////////////////////////////////////
			// naming
			void setName(const std::string &NewName)
			{
				MainName = NewName;
			}
			std::string& getName() const
			{
				if (MainName != std::string(""))
				{
					WholeName = MainName;
				}
				else
				{
					if (Obj)
						WholeName = std::to_string((size_t)Obj);
					else
						WholeName = std::string("Hndl_nNnO");
				}
				if (Num != 0)
				{
					WholeName += std::to_string(Num);
				}
				return WholeName;
			}
			void IncrementName()
			{
				Num++;
			}

		private:
			//////////////////////////////////////////////////////////
			// vars
			T* Obj;
			std::string MainName;
			mutable std::string WholeName;
			int Num;
		};
	}
}
