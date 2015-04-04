#pragma once

#include <vector>

namespace ZABS
{
	namespace Math
	{
		class Random
		{
		public:
			//rand
			static int InfluencedRand(std::vector<float> &Chances);
		};
	}
}