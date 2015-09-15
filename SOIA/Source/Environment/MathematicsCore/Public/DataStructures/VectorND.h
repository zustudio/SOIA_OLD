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
		std::vector<T> Values;
		std::string text;
	public:
		/////////////////////////////////////////////////////////
		// constructors
		VectorND(const std::vector<T> &NewVal)
		{
			Values = NewVal;
		}
		VectorND(const std::deque<T> &NewDeque)
		{
			Values = std::vector<T>();
			for (T element : NewDeque)
			{
				Values.push_back(element);
			}
		}
		VectorND(int dim)
		{
			Values = std::vector<T>();
			for (int i = 0; i < dim; i++)
			{
				Values.push_back(T());
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
			return Values.size();
		}
		VectorND<T> & Fill(T const & InValue)
		{
			for (T& value : Values)
			{
				value = InValue;
			}
			return *this;
		}
		//---- access operation ----
		T const & operator[](int i) const
		{
			if (i < Values.size())
			{
				return Values[i];
			}
			else
			{
				return T();
			}
		}
		T& operator [](int i)
		{
			if (i >= 0 && i < dim())
				return Values[i];
			else
			{
				for (int delta = i + 1 - dim(); delta > 0; delta--)
				{
					Values.push_back(0);
				}
				return Values[i];
			}
		}
		//---- list operation ----
		void intern_OpAdd(VectorND<T> const & a, VectorND<T> const & b, VectorND<T> &r) const
		{
			int n = std::fmax(a.dim(), b.dim());
			for (int i = 0; i < n; i++)
			{
				r[i] = a[i] + b[i];
			}
		}
		void intern_OpSubstract(VectorND<T> const & a, VectorND<T> const & b, VectorND<T> & r) const
		{
			int n = std::fmax(a.dim(), b.dim());
			for (int i = 0; i < n; i++)
			{
				r[i] = a[i] - b[i];
			}
		}
		VectorND<T> operator +(VectorND<T> const & InOther) const
		{
			VectorND<T> result = VectorND<T>(dim());
			intern_OpAdd((*this), InOther, result);
			return result;
		}
		VectorND<T> operator -(VectorND<T> const & InOther) const
		{
			VectorND<T> result = VectorND<T>(dim());
			intern_OpSubstract(*this, InOther, result);
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
			for (T element : Values)
			{
				result += element;
			}
			return result;
		}
		//---- scalar operation ----
		template<typename ScalarType>
		void intern_OpMult(VectorND<T> const & a, ScalarType const & b, VectorND<T> &r) const
		{
			int n = a.dim();
			for (int i_single = 0; i_single < n; i_single++)
			{
				r[i_single] = a[i_single] * b;
			}
		}
		VectorND<T> operator *(float a)
		{
			VectorND<T> result = VectorND<T>(dim());
			intern_OpMult(*this, a, result);
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
