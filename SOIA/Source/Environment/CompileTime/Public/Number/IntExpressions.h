
#pragma once

namespace Environment
{
	constexpr const int Encode4Bytes(char c0, char c1, char c2, char c3)
	{
		return (c0 + (c1 << 8) + (c2 << 16) + (c3 << 24));
	}

	constexpr const char Decode4Bytes(int Value, char n)
	{
		return (Value >> n * 8) & 0xFF;
	}

	constexpr const int NotZero(int Value)
	{
		return Value < 1 ?
			1 :
			Value;
	}
}