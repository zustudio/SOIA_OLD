
#pragma once

namespace Environment
{
	struct Vector4Int
	{
		constexpr Vector4Int(int InValue0, int InValue1, int InValue2, int InValue3)
			:
			Value0(InValue0),
			Value1(InValue1),
			Value2(InValue2),
			Value3(InValue3)
		{}

		constexpr const int Get(int InIndex)
		{
			return InIndex == 0 ?
				Value0 :
				InIndex == 1 ?
				Value1 :
				InIndex == 2 ?
				Value2 :
				Value3;
		}

		const int Value0;
		const int Value1;
		const int Value2;
		const int Value3;
	};
}