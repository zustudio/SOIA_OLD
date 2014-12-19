// c Maxim Urschumzew

#pragma once

namespace ZABS
{
	namespace Math
	{
		template<class T> class Vector2D
		{
		public:
			//////////////////////////////////////////////////////
			// data
			T X;
			T Y;
			/////////////////////////////////////////////////////
			// constructors
			Vector2D()
			{
				X = 0;
				Y = 0;
			}
			Vector2D(T newX, T newY)
			{
				X = newX;
				Y = newY;
			}
			Vector2D(const Vector2D<T> &equalVector)
			{
				X = equalVector.X;
				Y = equalVector.Y;
			}
			~Vector2D()
			{

			}
			/////////////////////////////////////////////////////////
			// math
			Vector2D<T> operator +(Vector2D<T> &a)
			{
				return Vector2D<T>(a.X + X, a.Y + Y);
			}
			Vector2D<T> operator *(int n)
			{
				return Vector2D<T>(X * n, Y * n);
			}
		};
	}
}
