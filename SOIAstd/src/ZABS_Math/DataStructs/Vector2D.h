// c Maxim Urschumzew

#pragma once

namespace ZABS
{
	namespace Math
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
			~Vector2D()
			{

			}
			/////////////////////////////////////////////////////////
			// math
			//---- list operation ----
			Vector2D<T> operator +(Vector2D<T> a)
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
			Vector2D<T> operator *(Vector2D<T> a)
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

			//---- scalar operation ----
			Vector2D<T> operator *(int n)
			{
				return Vector2D<T>(X * n, Y * n);
			}
		};
	}
}
