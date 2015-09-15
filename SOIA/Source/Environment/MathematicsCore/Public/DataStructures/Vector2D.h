// c Maxim Urschumzew

#pragma once

#include <cmath>
#include "VectorND.h"

namespace Environment
{
	template<class T> class Vector2D
	{
	public:
		/////////////////////////////////////////////////////////
		// data
		T X;
		T Y;
		/////////////////////////////////////////////////////////
		// constructors
		Vector2D(T newX = 0, T newY = 0)
		{
			X = newX;
			Y = newY;
		}
		Vector2D(VectorND<T> base)
		{
			X = base[0];
			Y = base[1];
		}
		~Vector2D()
		{

		}
		/////////////////////////////////////////////////////////
		// math
		//---- list operation ----
		Vector2D<T> operator +(Vector2D<T> a) const
		{
			return Vector2D<T>(a.X + X, a.Y + Y);
		}
		Vector2D<T> operator +=(Vector2D<T> a)
		{
			Vector2D<T> tmp(*this);
			X += a.X;
			Y += a.Y;
			return tmp;
		}
		Vector2D<T> operator -(Vector2D<T> a) const
		{
			return Vector2D<T>(X - a.X, Y - a.Y);
		}
		Vector2D<T> operator *(Vector2D<T> a) const
		{
			return Vector2D<T>(a.X *X, a.Y * Y);
		}
		Vector2D<T> operator *=(Vector2D<T> a)
		{
			Vector2D<T> tmp = Vector2D<T>(*this);
			X *= a.X;
			Y *= a.Y;
			return tmp;
		}
		Vector2D<T> Divide1()
		{
			return Vector2D<T>(1 / X, 1 / Y);
		}

		//---- scalar operation ----
		template<typename ScalarType>
		Vector2D<T> operator *(ScalarType const & n) const
		{
			return Vector2D<T>(ScalarType(X) * n, ScalarType(Y) * n);
		}

		///////////////////////////////////////////////////////////
		// conversion
		template<typename ToType>
		Vector2D<ToType> Convert()
		{
			return Vector2D<ToType>(X, Y);
		}

		///////////////////////////////////////////////////////////
		// vector math
		Vector2D<T> Normalized()
		{
			Vector2D<T> temp = *this;
			return Vector2D<T>(temp * (1/Length()));
		}
		T Length()
		{
			T back;
			back = std::sqrt(std::pow(X, 2) + std::pow(Y, 2));
			return back;
		}
		Vector2D<T> RotateZ(float angle)
		{
			Vector2D<T> temp = *this;
			double length = Length();
			double previousAngleToX = std::asin((temp.Normalized()).Y);
			previousAngleToX = X >= 0 ? previousAngleToX : 3.14159 - previousAngleToX;
			return Vector2D<T>(std::cos(previousAngleToX + angle), std::sin(previousAngleToX + angle)) * length;
		}
	};
}
