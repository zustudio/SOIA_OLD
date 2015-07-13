
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

		template<typename HeadType, typename... TailTypes>
		static constexpr const HeadType Minimum(const HeadType& HeadArgument, const TailTypes&... TailArguments)
		{
			return HeadArgument <= Minimum(TailArguments...)? HeadArgument : Minimum(TailArguments...);
		}
		template<typename LastType>
		static constexpr const LastType Minimum(const LastType& LastArgument)
		{
			return LastArgument;
		}

	};
}