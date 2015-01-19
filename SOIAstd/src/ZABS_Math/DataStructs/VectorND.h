// c Maxim Urschumzew

#pragma once

#include <cmath>
#include <vector>
#include <string>

namespace ZABS
{
	namespace Math
	{
		template<class T> class VectorND
		{
		private:
			/////////////////////////////////////////////////////////
			// data
			std::vector<T> val;
			std::string text;
		public:
			/////////////////////////////////////////////////////////
			// constructors
			VectorND(const std::vector<T> &NewVal)
			{
				val = NewVal;
			}
			VectorND(int dim, T defaultValue = 0)
			{
				val = std::vector<T>();
				for (int i = 0; i < dim; i++)
				{
					val.push_back(defaultValue);
				}
			}
			~VectorND()
			{

			}
			/////////////////////////////////////////////////////////
			// math
			//---- helpers ----
			int dim() const
			{
				return val.size();
			}
			//---- access operation ----
			T& operator [](T i)
			{
				if (i >= 0 && i < dim())
					return val[i];
				else
				{
					for (int delta = i + 1 - dim(); delta > 0; delta--)
					{
						val.push_back(0);
					}
					return val[i];
				}
			}
			//---- list operation ----
			void intern_OpAdd(VectorND<T> &a, VectorND<T> &b, VectorND<T> &r)
			{
				int n = std::fmax(a.dim(), b.dim());
				for (int i_single = 0; i_single < n; i_single++)
				{
					r[i_single] = a[i_single] + b[i_single];
				}
			}
			VectorND<T> operator +(VectorND<T> a)
			{
				VectorND<T> result = VectorND<T>(1);
				intern_OpAdd((*this), a, result);
				return result;
			}
			VectorND<T> operator +=(VectorND<T> a)
			{
				VectorND<T> tmp(*this);
				intern_OpAdd(*this, a, *this);
				return tmp;
			}
			/////////////////////////////////////////////////////////
			// conversions
			operator std::string& ()
			{
				text = std::string("(");
				int n = dim();
				for (int i = 0; i < n; i++)
				{
					text += (std::to_string((*this)[i]) + "|");
				}
				text += ")";
				return text;
			}
		};
	}
}
