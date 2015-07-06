// c Maxim Urschumzew

#pragma once

#include <cmath>
#include <vector>
#include <deque>
#include <string>

namespace Environment
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
		VectorND(const std::deque<T> &NewDeque)
		{
			val = std::vector<T>();
			for (T element : NewDeque)
			{
				val.push_back(element);
			}
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
		T Sum()
		{
			T result = 0;
			for (T element : val)
			{
				result += element;
			}
			return result;
		}
		//---- scalar operation ----
		void intern_OpMult(VectorND<T> &a, VectorND<T> &b, VectorND<T> &r)
		{
			int n = std::fmax(a.dim(), b.dim());
			for (int i_single = 0; i_single < n; i_single++)
			{
				r[i_single] = a[i_single] * b[i_single];
			}
		}
		VectorND<T> operator *(float a)
		{
			VectorND<T> result = VectorND<T>(1);
			VectorND<T> other = VectorND<T>(dim());
			for (int i = 0; i < dim(); i++)
			{
				other[i] = a;
			}
			intern_OpMult((*this), other, result);
			return result;
		}
		/////////////////////////////////////////////////////////
		// conversions
		std::string to_intstring()
		{
			text = std::string("(");
			int n = dim();
			for (int i = 0; i < n; i++)
			{
				text += (std::to_string((int)std::round((*this)[i])) + "|");
			}
			text += ")";
			return text;
		}
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
