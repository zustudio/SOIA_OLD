
#pragma once

namespace Environment
{
	template<char InVal>
	struct ConstExprChar
	{
		static constexpr const char Value = InVal;
	};
}
