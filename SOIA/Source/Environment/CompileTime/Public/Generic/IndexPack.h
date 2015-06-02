
#pragma once

namespace Environment
{
	template<typename InAction, int InCurrentIndex, int... InTailIndices>
	struct UsingEveryIndex_Helper : UsingEveryIndex_Helper<InAction, InCurrentIndex - 1, InCurrentIndex - 1, InTailIndices...>
	{};

	template<typename InAction, int... InTailIndices>
	struct UsingEveryIndex_Helper<InAction, 0, InTailIndices...>
	{
		using Result = typename InAction::template Inner<InTailIndices...>;
	};

	template<int MaxIndex, typename InAction>
	using UsingEveryIndex = typename UsingEveryIndex_Helper<InAction, MaxIndex>::Result;
}