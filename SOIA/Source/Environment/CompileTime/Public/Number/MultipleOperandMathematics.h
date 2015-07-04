
#pragma once

namespace Environment
{
	struct CompileTime
	{
		template<typename HeadType, typename... TailTypes>
		static constexpr const HeadType Add(const HeadType& HeadArgument, const TailTypes&... TailArguments)
		{
			return HeadArgument + Add(TailArguments...);
		}
		template<typename LastType>
		static constexpr const LastType Add(const LastType& LastArgument)
		{
			return LastArgument;
		}

	};
}