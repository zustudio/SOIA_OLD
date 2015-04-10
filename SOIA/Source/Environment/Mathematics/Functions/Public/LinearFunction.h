
#pragma once

#include <vector>

namespace ZABS
{
	namespace Math
	{
		class __declspec(dllexport) LinearFunction
		{
		public:
			static float get_f(float x, const std::vector<float> &params);
			static float get_reverse_x(float f, const std::vector<float> &params);
		};
	}
}