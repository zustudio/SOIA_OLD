
#pragma once

#include <vector>

namespace Environment
{
	class D1D1FunctionInterface
	{
	public:
		virtual double Calculate(double InX) = 0;

	public:
		double operator() (double InX)
		{
			return Calculate(InX);
		}
	};
}