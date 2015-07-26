
#pragma once

namespace Environment
{
#ifdef _MSC_VER
	template<typename TestType>
	struct HasMemberAccessOperator
	{
		__if_exists(TestType::operator->)
		{
			static constexpr const bool value = true;
		}
		__if_not_exists(TestType::operator->)
		{
			static constexpr const bool value = false;
		}
	};
#endif
}