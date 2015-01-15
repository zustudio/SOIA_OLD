// c Maxim Urschumzew

#pragma once

#include <cmath>
#include <vector>

namespace ZABS
{
	namespace Math
	{
		template<class T> class VectorND
		{
		public:
			/////////////////////////////////////////////////////////
			// data
			std::vector<T> val;
			/////////////////////////////////////////////////////////
			// constructors
			VectorND(const std::vector<T> &NewVal)
			{
				val = NewVal;
			}
			VectorND(int dim)
			{
				val = std::vector<T>();
				for (int i = 0; i < dim; i++)
				{
					val.push_back(0);
				}
			}
			~VectorND()
			{

			}
			/////////////////////////////////////////////////////////
			// math
			//---- helpers ----
			int dim()
			{
				return val.size();
			}
			//---- access operation ----
			T& operator [](int i)
			{
				if (i >= 0 && i < dim())
					return val[i];
				else
					return 0;
			}
			//---- list operation ----
			VectorND<T> operator +(VectorND<T> a)
			{
				int n = std::fmax(this->din(), a->dim());
				VectorND<T> result = VectorND<T>(n);
				for (int i_single = 0; i_single < n; i_single++)
				{
					result[i_single] = (*this)[i_single] + a[i_single];
				}
				return result;
			}
			VectorND<T> operator +=(VectorND<T> a)
			{
				VectorND<T> tmp(*this);
				tmp = tmp + a;
				return tmp;
			}
			/*VectorND<T> operator -(VectorND<T> a)
			{
				return VectorND<T>(X - a.X, Y - a.Y);
			}
			VectorND<T> operator *(VectorND<T> a)
			{
				return VectorND<T>(a.X *X, a.Y * Y);
			}
			VectorND<T> operator *=(VectorND<T> a)
			{
				VectorND<T> tmp = VectorND<T>(*this);
				X *= a.X;
				Y *= a.Y;
				return tmp;
			}*/

			//---- scalar operation ----
			/*VectorND<T> operator *(T n)
			{
				return VectorND<T>(X * n, Y * n);
			}*/
		};
	}
}
