
#pragma once

#include <array>

namespace Environment
{
	class CharArrayLiteral
	{
	public:
		const char* const text_ptr;
		unsigned int text_size;
	public:
		template <unsigned int N>
		constexpr CharArrayLiteral(const char(&aStr)[N]) :
			text_ptr(aStr), text_size(N - 1)
		{
			static_assert(N >= 1, "Invalid string literal! Length is zero!");
			static_assert(N < 255, "String Literal is too long too fit into char!");
		};

		constexpr CharArrayLiteral(const char* const InPtr, unsigned int InSize)
			:
			text_ptr(InPtr),
			text_size(InSize)
		{}
	};
}