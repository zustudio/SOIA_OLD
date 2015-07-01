
#pragma once

#include "VectorND.h"

#include <vector>

namespace ZABS
{
	namespace Math
	{
		template<typename T>
		class Matrix2D
		{
		public:
			/////////////////////////////////////////////////
			// functions
			//---- init ----
			Matrix2D(int NewSizeX = 1, int NewSizeY = 1, const T &NewContent = 0)
			{
				Content = std::vector < T >();

				Resize(NewSizeX, NewSizeY, NewContent);
			}

			//---- properties ----
			VectorND<int> Dim()
			{
				return VectorND<int>({ SizeX, SizeY });
			}
			void Resize(int NewSizeX, int NewSizeY, T value)
			{
				//set new size
				SizeX = NewSizeX;
				SizeY = NewSizeY;
				Content.resize(SizeX * SizeY);
				
				//reset elements
				Fill(value);
			}

			//---- single access ----
			void set(int x, int y, const T &NewContent)
			{
				T* Element = get(x, y);
				if (Element)
					*Element = NewContent;
			}
			T* get(int x, int y)
			{
				if (x < SizeX && y < SizeY)
					return &Content[x + y * SizeY];
				else
					return nullptr;
			}
			
			//---- multiple access ----
			void Fill(const T &NewContent)
			{
				for (T element : Content)
				{
					element = NewContent;
				}
			}
			VectorND<T> GetRow(int y)
			{
				std::vector<T> result = std::vector<T>();
				for (int x = 0; x < SizeX; x++)
				{
					result.push_back(*get(x, y));
				}
				return VectorND<T>(result);
			}
			VectorND<T> GetColumn(int x)
			{
				std::vector<T> result = std::vector<T>();
				for (int y = 0; y < SizeY; y++)
				{
					result.push_back(*get(x, y));
				}
				return VectorND<T>(result);
			}

			//---- converting ----
			std::string to_string()
			{
				std::string result;
				for (int y = 0; y < SizeY; y++)
				{
					result += GetRow(y).to_intstring() + std::string("\n");
				}
				return result;
			}

		private:
			/////////////////////////////////////////////////
			// variables
			int SizeX;
			int SizeY;
			std::vector<T> Content;
		};
	}
}
