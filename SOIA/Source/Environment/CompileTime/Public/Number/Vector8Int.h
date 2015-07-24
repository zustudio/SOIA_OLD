
#pragma once

namespace Environment
{
	struct Vector8Int
	{
		constexpr Vector8Int(int InValue0, int InValue1, int InValue2, int InValue3, int InValue4, int InValue5, int InValue6, int InValue7)
			:
			Value0(InValue0),
			Value1(InValue1),
			Value2(InValue2),
			Value3(InValue3),
			Value4(InValue4),
			Value5(InValue5),
			Value6(InValue6),
			Value7(InValue7)
		{}

		constexpr const int Get(int InIndex) const
		{
			return InIndex == 0 ?
				Value0 :
				InIndex == 1 ?
				Value1 :
				InIndex == 2 ?
				Value2 :
				InIndex == 3 ?
				Value3 :
				InIndex == 4 ?
				Value4 :
				InIndex == 5 ?
				Value5 :
				InIndex == 6 ?
				Value6 :
				Value7;
		}
		const int Value0;
		const int Value1;
		const int Value2;
		const int Value3;
		const int Value4;
		const int Value5;
		const int Value6;
		const int Value7;
	};
}